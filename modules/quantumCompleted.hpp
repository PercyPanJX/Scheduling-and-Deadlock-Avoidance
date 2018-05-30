/*
 * quantumCompleted.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef QUANTUMCOMPLETED_HPP_
#define QUANTUMCOMPLETED_HPP_


#include "printQueues.hpp"

void addJob(Job job);
void distributeJobs();
void currentJobFinished();
void currentJobUnfinishedInQuantum();
void completedQuantum();

void addJob(Job job){

	//if job's need memory which is not enough by cpu's max memory, ignore
	//if job's max devices which is not enough by cpu's max device num, ignore
	if(job.getMemory() > sys.getMemory()
			|| job.getMaxDevices() > sys.getDeviceNum()){
//		cout << "memory or devices over!!! => Job: " << job.getID() << endl;
		return;
	}

	//if job's memory need is smaller than current system available memory,
	//it goes into ready queue, otherwise, goes into hold queues based on priority
	if(job.getMemory() <= sys.getAvailableMemory()){
		RQ.push(job);
		sys.decreaseAvailableMemory(job);
//		cout << "Job has been pushed into ready queue => Job:  " << job.getID() << endl;
	}else{
		if(job.getPriority() == 1){
			HQ1.push(job);
//			cout << "Job has been pushed into HQ1 => Job: " << job.getID() << endl;
		} else {
			HQ2.push(job);
//			cout << "Job has been pushed into HQ2 => Job: " << job.getID() << endl;
		}
	}

	//if cpu is idle time and ready queue is not empty, start the job
	if(sys.getIdle() && !RQ.empty()){
		int startTime = RQ.front().getArrivalTime();
		if(startTime > currentTime) currentTime = startTime; // update current time
		RQ.front().setStartTime(currentTime); //set start time for the job
		sys.startJob(RQ.front(), currentTime);
//		cout << "Job has been started into cpu: " << job.getID() << endl;
		RQ.pop();
	}

	return;
}

void distributeJobs(){

	//hold queue1 check
	//if the cpu has enough memory for jobs join ready queue
	while(!HQ1.empty()){
		Job job = HQ1.front();
		if(sys.getMemory() <= sys.getAvailableMemory()){
			RQ.push(job);
			HQ1.pop();
		}else{
			break;
		}
	}

	//hold queue2 check
	while(!HQ2.empty()){
		Job job = HQ2.front();
		if(sys.getMemory() <= sys.getAvailableMemory()){
			RQ.push(job);
			HQ2.pop();
		}else{
			break;
		}
	}


	//ready queue pop into cpu, running the first job from RQ
	if(!RQ.empty() && sys.getIdle()){
		sys.startJob(RQ.front(), currentTime);
		RQ.pop();
	}

}

void currentJobFinished(){
	Job currentJob = sys.getCurrentJob();
	//set current Time to this job's finished time
	currentTime += currentJob.getRemainingTime();

	//set current Job to 0 remaining time
	currentJob.decreaseRemainingTime(currentJob.getRemainingTime());

	// store current job's finished time
	currentJob.setFinishTime(currentTime);

	//release all allocated devices for the job
	currentJob.releaseAllAllocatedDevices();

	//terminate current job
	sys.terminateJob();

	//release job's devices
	sys.increaseAvailableDevices(currentJob.getDevicesRequest());

	// current finished job joins completed queue
	CQ.push(currentJob);

	//Using banker's algorithm to check wait queue
	queue<Job> processes;
	readyQueue tq = RQ;
	while(!tq.empty()){
		processes.push(tq.front());
		tq.pop();
	}

	//continue adding wait queue's jobs into ready queue to check if the
	//system is safe, if so, added, if not, stay in wait queue
	queue<Job> tmpWQ; //tmp queue is for storing the jobs couldn't added into RQ
	while(!WQ.empty()){
		Job tmp = WQ.front();
		processes.push(tmp);

		if(releaseBanker(processes)){ //if it is safe, add the job into ready queue
			RQ.push(tmp); //if the tmp job could be added, push to ready Q
		}else{
			tmpWQ.push(tmp); // if the tmp job couldn't, push to tmp Q
		}
		WQ.pop(); //pop ready queue
	}
	WQ =tmpWQ; // give back the ready queue with left jobs

//	cout << "\n-----JOB FINISHED------\n";
//	printQueues();

}

void currentJobUnfinishedInQuantum(){
	//The Job unfinished before current quantum finished

	Job currentJob = sys.getCurrentJob();

	//current time add to current + quantum
	currentTime += QUANTUM;

	//current job's remaining time - quantum
	currentJob.decreaseRemainingTime(QUANTUM);

	//current job joins ready queue
	RQ.push(currentJob);

	//terminate current job
	sys.terminateJob();
}

void completedQuantum(){

	if(sys.getIdle() == false){

		//get current running job
		Job currentJob = sys.getCurrentJob();

		//if current job finish,
		if(currentJob.getRemainingTime() <= QUANTUM){
			currentJobFinished();
		}

		//current job unfinished
		else{
			currentJobUnfinishedInQuantum();
		}
	}

	//check current status after jobs get out of the cpu
	//hold queue 1 & 2, ready queue status
	//next cpu's status
	distributeJobs();
}


#endif /* QUANTUMCOMPLETED_HPP_ */
