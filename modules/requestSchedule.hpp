/*
 * requestSchedule.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef REQUESTSCHEDULE_HPP_
#define REQUESTSCHEDULE_HPP_

#include "releaseSchedule.hpp"

/////////////////////////////////////////////////////////
void doRequest(Request r){
	// Request happens after quantum time.

	if(!sys.getIdle() && r.getID() == sys.getCurrentJob().getID()) {
		// if there is job running in the cpu
		// if request jobID is the running jobID
		// terminate job.

		Job currentJob = sys.getCurrentJob();
		sys.terminateJob();

		currentJob.increaseDevicesRequest(r.getDeviceNum());

//		cout << "add request => Job " << currentJob.getID() << " Devices Need: " << currentJob.getDevicesRequest() << endl;

		currentJob.decreaseRemainingTime(r.getRequestTime() - currentTime);

		/////////////////
		// run banker's algorithm
		queue<Job> processes;
		readyQueue tq = RQ;
		while(!tq.empty()){
			processes.push(tq.front());
			tq.pop();
		}
		processes.push(currentJob);  // Push the running process id

		int currentJobD = currentJob.getDevicesAllocated();

		if(requestBanker(processes, r) && sys.getAvailableDevices() >= 0) {
				// request granted. Allocated devices to
				// the job, decreases cpu's devices
			currentJob.setAllocatedDevices(r.getDeviceNum());
			sys.decreaseAvailableDevices(r.getDeviceNum());
			RQ.push(currentJob); // push to ready queue
		} else { // request rejected.
			currentJob.releaseAllAllocatedDevices();
			sys.increaseAvailableDevices(currentJobD);
			WQ.push(currentJob);
		}

		//Start the next job
		if(!RQ.empty()){
			currentTime = r.getRequestTime();
			sys.startJob(RQ.front(), currentTime);
			RQ.pop();
		}

	} else {
		// else ignore this request.
		return;
	}
}

void requestSchedule(Request r){

	//get the difference between the adding job startTime with current time
	int gapTime = r.getRequestTime() - currentTime;

	//Completed all quantum times until the gap time is shorter than one quantum
	while(gapTime >= QUANTUM){

		completedQuantum(); // complete one quantum

		if(sys.getIdle()) currentTime += QUANTUM;
			// if it is idle time,
			// current time is added quantum
			// because current time haven't been
			// added in completedQuantum function

		gapTime = r.getRequestTime() - currentTime; //update gapTime

	}

	//If there is job running in the cpu and the job has shorter time
	//than gaptime, job finished first
	if(!sys.getIdle() && sys.getCurrentJob().getRemainingTime() <= gapTime){
		currentJobFinished(); // finish current running job
		distributeJobs(); // check queues
	}

	//do request
	doRequest(r);
}


#endif /* REQUESTSCHEDULE_HPP_ */
