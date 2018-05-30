/*
 * releaseSchedule.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef RELEASESCHEDULE_HPP_
#define RELEASESCHEDULE_HPP_

#include "jobSchedule.hpp"


void doRelease(Release r){

	if(sys.getIdle() == false
			&& r.getID() == sys.getCurrentJob().getID()) {
		// if release jobID is the running jobID
		// terminate job, and decrease current devices.

		Job currentJob = sys.getCurrentJob();

//		cout << "previous device available" << sys.getAvailableDevices() << endl;

		//terminate current running job and release devices
		sys.terminateJob();
		sys.increaseAvailableDevices(r.getDeviceNum());

		//decrease allocated devices and request
		currentJob.releaseAllocatedDevices(r.getDeviceNum());
		currentJob.decreaseDevicesRequest(r.getDeviceNum());
		currentJob.decreaseRemainingTime(r.getReleaseTime() - currentTime);

//		cout << "devices request:" << currentJob.getDevicesAllocated();
//		cout << "devices release " << r.getDeviceNum() << endl;
//		cout << "current device available " << sys.getAvailableDevices() << endl;

		/////////////////
		// run banker's algorithm
		RQ.push(currentJob);
		queue<Job> processes;
		readyQueue tq = RQ;
		while(!tq.empty()){
			processes.push(tq.front());
			tq.pop();
		}

		queue<Job> tmpWQ;
		while(!WQ.empty()){
			Job tmp = WQ.front();
			processes.push(tmp);
//			cout << "Current tmp job devices request: " << tmp.getDeviceRequest();
			if(releaseBanker(processes)){
				tmp.setAllocatedDevices(tmp.getDevicesRequest());
				RQ.push(tmp); //if the tmp job could be added, push to ready Q
				sys.decreaseAvailableDevices(tmp.getDevicesRequest());
			}else{
				tmpWQ.push(tmp); // if the tmp job couldn't, push to tmp Q
			}
			WQ.pop(); //pop ready queue
		}

		WQ =tmpWQ; // give back the ready queue with left jobs

		//Start the next job
		if(!RQ.empty()){
			currentTime = r.getReleaseTime();
			sys.startJob(RQ.front(), currentTime);
			RQ.pop();
		}

	} else {
		// else ignore this release.
		return;
	}
}

void releaseSchedule(Release r){

	//get the difference between the adding job startTime with current time
	int gapTime = r.getReleaseTime() - currentTime;

	//Completed all quantum times until the gap time is shorter than one quantum
	while(gapTime >= QUANTUM){

		completedQuantum(); // complete one quantum

		if(sys.getIdle()) currentTime += QUANTUM;
			// if it is idle time,
			// current time is added quantum
			// because current time haven't been
			// added in completedQuantum function

		gapTime = r.getReleaseTime() - currentTime; //update gapTime
	}

	//If there is job running in the cpu and the job has shorter time
	//than gaptime, job finished first
	if(!sys.getIdle() && sys.getCurrentJob().getRemainingTime() <= gapTime){
		currentJobFinished(); // finish current running job
		distributeJobs(); // check queues
	}

	//do request
	doRelease(r);
}


#endif /* RELEASESCHEDULE_HPP_ */
