/*
 * System.hpp
 *
 *  Created on: May 19, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef MODULES_CLASSES_SYSTEM_HPP_
#define MODULES_CLASSES_SYSTEM_HPP_


#include "CPU.hpp"

class System{
	int startTime,  memory, deviceNum, Quantum, availableMemory,availableDevices;
	CPU cpu;

public:
	System(){
		startTime = 0;
		memory = 0;
		deviceNum = 0;
		Quantum = 0;
		availableMemory = 0;
		availableDevices = 0;
		cpu = CPU();
	}
	System(int s, int m, int dn, int q){
		startTime = s;
		memory = m;
		deviceNum = dn;
		Quantum = q;
		availableMemory = m;
		availableDevices = dn;
		cpu = CPU();
	}
	int getMemory() {
		return memory;
	}
	int getMaxDevices(){
		return deviceNum;
	}
	int getDeviceNum() {
		return deviceNum;
	}
	int getAvailableMemory() {
		return availableMemory;
	}
	int getAvailableDevices() {
		return availableDevices;
	}
	Job getCurrentJob(){
		return cpu.currentJob;
	}

	bool getIdle() {
		return cpu.idle;
	}

	void setCurrentDevices(int deviceNum) {
		availableDevices = deviceNum;
	}

	void setCurrentJob(Job j){
		cpu.currentJob = j;
	}

	void startJob(Job job, int currentTime){
		cpu.idle = false;
		cpu.currentJob = job;
		cpu.currentJob.setStartTime(currentTime);

	}
	void terminateJob(){
		cpu.idle = true;
		cpu.currentJob = Job();

	}

	void increaseAvailableDevices(int d) {
		availableDevices += d;
		if(availableDevices > deviceNum){
			cout << "Too many available devices for system";
		}
	}

	void decreaseAvailableDevices(int d) {
		availableDevices -= d;
		if(availableDevices < 0){
			cout << "ERROR: Job: " << cpu.currentJob.getID() << endl;
			cout << "Too many devices request for system";
		}
	}

	void increaseAvailableMemory(Job j){
		availableMemory += j.getMemory();
	}
	void decreaseAvailableMemory(Job j){
		availableMemory -= j.getMemory();
	}

	void print(){
		cout << "Start Time: " << startTime << endl;
		cout << "Main Memory: " << memory << endl;
		cout << "Device Number: " << deviceNum << endl;
		cout << "Quantum: " << Quantum << endl;
		cout << "Available Devices: " << availableDevices << endl;
		cout << "Available Memory: " << availableMemory << endl;
		cout << endl;

		output << "Start Time: " << startTime << endl;
		output << "Main Memory: " << memory << endl;
		output << "Device Number: " << deviceNum << endl;
		output << "Quantum: " << Quantum << endl;
		output << "Available Devices: " << availableDevices << endl;
		output << "Available Memory: " << availableMemory << endl;
		output << endl;
	}
};




#endif /* MODULES_CLASSES_SYSTEM_HPP_ */
