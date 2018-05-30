/*
 * bankAlgorithm.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef BANKALGORITHM_HPP_
#define BANKALGORITHM_HPP_

#include "linker.hpp"

void calculateNeed(int processNum, int need[], int maxm[], int alloc[]);
bool isSafe(queue<Job> processes);

////////////////////////////////////////////////////////////
// Function to find the need of each process
// RQ.size() + 1 stands for the total number of processes
// MAXDEVICES stands for devices.

bool isSafe(queue<Job> processes, System tmpSys){

	//cout << tmpSys.getAvailableDevices() << endl;

	int processNum = processes.size();

	////// maxDevices
	int processesID[processNum];
	int maxm[processNum];
	int alloc[processNum];
	int need[processNum];

	int i = 0;
	while(!processes.empty()){
		processesID[i] = processes.front().getID();

		maxm[i] = processes.front().getMaxDevices();

		alloc[i] = processes.front().getDevicesAllocated() ;

		need[i] = maxm[i] - alloc[i];

		processes.pop();

		cout << "ID: " << processesID[i] << " max: " << maxm[i] << " Allo: " << alloc[i] <<
				" Need: " << need[i] << endl;

		i++ ;
	}


	// Make a copy of available resources
	int work = tmpSys.getAvailableDevices() ;
	cout << "System Available devices: " << tmpSys.getAvailableDevices() << endl;

	// To store safe sequence
	int safeSeq[processNum];


	// Mark all processes as unfinish
	bool finish[processNum];
	for(int i = 0; i < processNum; i++) {
		finish[i] = 0;
	}


	// While all processes are not finished
	// or system is not in safe state.
	int count = 0;


	while (count < processNum) {
		// Find a process which is not finish and
		// whose needs can be satisfied with current
		// work[] resources

		bool found = false;

		for (int p = 0; p < processNum; p++)
		{
			// First check if a process is finished,
			// if no, go for next condition
			if (finish[p] == 0){

				int j;
				for(j = 0; j < processNum; j++){
					if(need[p] > work) break;
				}

				// If needs of p were satisfied.
				if (j == processNum){
					// Add the allocated resources of
					// current P to the available/work
					// resources i.e.free the resources
					work += alloc[p];

					// Add this process to safe sequence.
					safeSeq[count++] = processesID[p];

					// Mark this p as finished
					finish[p] = 1;

					found = true;
				}
			}
 		}

		// If we could not find a next process in safe
		// sequence.
		if (found == false)
		{
			cout << "System is not in safe state" << endl;
			output << "System is not in safe state" << endl;
			return false;
		}
	}

	//Just compare the current available devices and Job's total devices


    // If system is in safe state then
    // safe sequence will be as below
//    cout << "System is in safe state.\nSafe"
//         " sequence is: ";
//    for (int i = 0; i < processNum; i++)
//        cout << safeSeq[i] << " ";
//    cout << endl;


    return true;
}

bool requestBanker(queue<Job> processes, Request r){

	if(r.getDeviceNum() > sys.getAvailableDevices()){
		cout << "Unsafe State" << endl;
		return false;
	}

	processes.back().setAllocatedDevices(r.getDeviceNum());

	System tmpSys = sys;

	tmpSys.decreaseAvailableDevices(r.getDeviceNum());

	bool safe = isSafe(processes,tmpSys);

	return safe;
}

bool releaseBanker(queue<Job> processes){

	if(processes.back().getDevicesRequest() > sys.getAvailableDevices()){
		cout << "Unsafe state" << endl;
		return false;
	}

	bool safe = isSafe(processes, sys);

	return safe;
}


#endif /* BANKALGORITHM_HPP_ */
