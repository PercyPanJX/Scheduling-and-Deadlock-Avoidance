/*
 * printSchedule.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef PRINTSCHEDULE_HPP_
#define PRINTSCHEDULE_HPP_

#include "quantumCompleted.hpp"

void printStatus(int printTime){

	//Store current Status
	int tmpCurrentTime = currentTime;
	HoldQueue1 tmpCurrentHQ1 = HQ1;
	HoldQueue2 tmpCurrentHQ2 = HQ2;
	readyQueue tmpCurrentRQ = RQ;
	queue<Job> tmpCurrentWQ = WQ;
	CompletedQueue tmpCuurentCQ = CQ;
	System tmpCurrentSys = sys;

	//get the difference between the adding job startTime with current time
	int gapTime = printTime - currentTime;
	//cout << endl << "scanering's previous current time"  << currentTime << endl;

	//Completed all quantum times until the gap time is shorter than one quantum
	while(gapTime >= QUANTUM){

		completedQuantum(); // complete one quantum
		if(sys.getIdle()) currentTime += QUANTUM;
			// if it is idle time,
			// current time is added quantum
			// because current time haven't been
			// added in completedQuantum function

		gapTime = printTime - currentTime; //update gapTime

	}

	//If there is job running in the cpu and the job has shorter time
	//than gaptime, job finished first
	if(!sys.getIdle() && sys.getCurrentJob().getRemainingTime() <= gapTime){
		currentJobFinished(); // finish current running job
		distributeJobs(); // check queues
	}

	//change remaining time for current running job if there is running job
	if(!sys.getIdle()){
		Job j = sys.getCurrentJob();
		j.decreaseRemainingTime(printTime-currentTime);
		sys.setCurrentJob(j);
	}

	//currentTime changed to print Time
	currentTime = printTime;

	//print the queses
	printQueues();
	cout << endl;

	//Give back the stored status
	currentTime = tmpCurrentTime;
	HQ1 = tmpCurrentHQ1;
	HQ2 = tmpCurrentHQ2;
	RQ = tmpCurrentRQ;
	WQ = tmpCurrentWQ;
	sys = tmpCurrentSys;

}

#endif /* PRINTSCHEDULE_HPP_ */
