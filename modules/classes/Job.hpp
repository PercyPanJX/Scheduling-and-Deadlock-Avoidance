/*
 * Job.hpp
 *
 *  Created on: 2018/5/12
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef JOB_HPP_
#define JOB_HPP_

#include "basePackageLinker.hpp"

class Job{
	int arrivalTime, jobID, memory, maxDevices, runTime, priority;

	int turnaroundTime;
	int startTime;   //Job's first start time
	int remainingTime; //Job's remaining time
	int finishTime;  //Job's finished time
	double weightedTurnaroundTime; // job's weited turnaround time

	int devicesAllocated;
	int devicesRequest; //jobs' requested devices

	bool start;

public:
	Job(){};
	Job(int s, int id, int m, int maxD, int rt, int p){
		arrivalTime = s;
		jobID = id;
		memory = m;
		maxDevices = maxD;
		runTime = rt;
		priority = p;

		//time handling variables
		start = false;
		startTime = -1;
		remainingTime = runTime;
		finishTime = -1;
		turnaroundTime = -1;
		weightedTurnaroundTime = -1;

		//devices handling variables
		devicesAllocated = 0;
		devicesRequest = 0;
	}

	int getArrivalTime(){
		return arrivalTime;
	}
	int getID(){
		return jobID;
	}
	int getMemory(){
		return memory;
	}
	int getMaxDevices(){
		return maxDevices;
	}
	int getRuntime(){
		return runTime;
	}
	int getPriority(){
		return priority;
	}
	int getDevicesAllocated(){
		return devicesAllocated;
	}
	int getTurnaroundTime(){
		return turnaroundTime;
	}
	int getRemainingTime(){
		return remainingTime;
	}
	int getDevicesRequest(){
		return devicesRequest;
	}
	int getStartTime(){
		return startTime;
	}


	//Time handling functions
	void setStartTime(int t){
		//if the job is first time running, set start time for it
		if(!start){
			start = true;
			startTime = t;
		}
	}
	void decreaseRemainingTime(int t){
		remainingTime -= t;
	}
	void setFinishTime(int f){
		finishTime = f;

		turnaroundTime = finishTime - arrivalTime; //compute turnaround time
		weightedTurnaroundTime = (double)turnaroundTime / runTime; //compute waited turnaround time
	}

	////Devices handling functions
	void setAllocatedDevices(int d){
		//give job devices
		devicesAllocated += d;
		if(devicesAllocated > maxDevices){
			cout << "ID: " << jobID << endl;
			cout << "DevicesAllocated: " << devicesAllocated << endl;
			cout << "Too many devices request" << endl;
		}
	}
	void releaseAllocatedDevices(int d){
		//release devices
		devicesAllocated -= d;
	}
	void releaseAllAllocatedDevices(){
		devicesAllocated = 0;
	}
	void increaseDevicesRequest(int d){
		devicesRequest += d;
	}
	void decreaseDevicesRequest(int d){
		devicesRequest -= d;
	}


	////print function
	void print(){
		cout << "Job" << jobID <<endl;
		cout << "Arribal Time: " << arrivalTime << endl;
		cout << "Total run time: " << runTime << endl;
		cout << "Priority: " << priority << endl;
		cout << "Devices allocated: " <<  devicesAllocated << endl;
		cout << "Devices requested: " <<  devicesRequest << endl;
		cout << "Start time: " << startTime << endl;
		cout << "Finish time " << finishTime << endl;
		cout << "Turnaround time: " << turnaroundTime << endl;
		cout << "Remaining time: " << remainingTime << endl;
		cout << "Weighted turnaround time: " << weightedTurnaroundTime << endl;
		cout << endl;

		output << "Job" << jobID <<endl;
		output << "Arribal Time: " << arrivalTime << endl;
		output << "Total run time: " << runTime << endl;
		output << "Priority: " << priority << endl;
		output << "Devices allocated: " <<  devicesAllocated << endl;
		output << "Devices requested: " <<  devicesRequest << endl;
		output << "Start time: " << startTime << endl;
		output << "Finish time " << finishTime << endl;
		output << "Turnaround time: " << turnaroundTime << endl;
		output << "Remaining time: " << remainingTime << endl;
		output << "Weighted turnaround time: " << weightedTurnaroundTime << endl;
		output << endl;

	}

};



#endif /* JOB_HPP_ */
