/*
 * addJobFuncions.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */



#ifndef JOBSCHEDULE_HPP_
#define JOBSCHEDULE_HPP_

#include "printSchedule.hpp"

void jobSchedule(Job job){

	//get the difference between the adding job startTime with current time
	int gapTime = job.getArrivalTime() - currentTime;

	//Completed all quantum times until the gap time is shorter than one quantum
	while(gapTime >= QUANTUM){

		completedQuantum(); // complete one quantum

		if(sys.getIdle()) currentTime += QUANTUM; // if it is idle time,
												 // current time is added quantum
												 // because current time haven't been
												 // added in completedQuantum function

		gapTime = job.getArrivalTime() - currentTime; //update gapTime

	}

	//If cpu is in idle time, current time should be the job, job getting into
	// cpu immediately. If not and current running job's remaining time less than
	// gap time, current running job need finished and check other queues.
	if(sys.getIdle()){
		currentTime = job.getArrivalTime();
	}else{
		if(sys.getCurrentJob().getRemainingTime() <= gapTime){
			currentJobFinished(); // finish current running job
			distributeJobs(); // check queues
		}
	}

	//After internal function finished, job needs to be added into system
	addJob(job);

	//printQueues(currentTime);

}



#endif /* JOBSCHEDULE_HPP_ */
