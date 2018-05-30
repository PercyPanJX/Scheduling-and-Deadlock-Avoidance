/*
 * fileReader.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include"requestSchedule.hpp"


System systemSensor(ifstream &infile);
Job jobSensor(ifstream &infile);
Request requestSensor(ifstream &infile);
Release releaseSensor(ifstream &infile);

void generator(ifstream &infile){
	string tmp;
	while(infile >> tmp){
		if (tmp == "C"){
			sys = systemSensor(infile);
			cout << "\n-------- Get A System info --------" << endl;
			output << "\n-------- Get A System info --------" << endl;
			continue;
		}

		else if (tmp == "A"){
			Job job = jobSensor(infile) ;
			cout << "\n-------- Get A Job --------" << endl;
			output << "\n-------- Get A Job --------" << endl;
			jobSchedule(job);
			continue;
		}

		else if(tmp == "Q"){
			Request request = requestSensor(infile);
			cout << "\n-------- currentTime: --------" <<request.getRequestTime()<<endl;
			cout << "\n-------- Get A request --------" << endl;
			output << "\n-------- Get A request --------" << endl;
			requestSchedule(request);
			continue;
		}

		else if(tmp == "L"){
			Release release = releaseSensor(infile);
			cout << "\n-------- Get A release --------" << endl;
			output << "\n-------- Get A release --------" << endl;
			releaseSchedule(release);
			continue;
		}

		else if(tmp == "D"){
			//special print
			int printTime;
			infile >> tmp;
			printTime = stoi(tmp);

			cout << "\n-------- Get A Print Request --------" <<endl;
			output << "\n-------- Get A Print Request --------" <<endl;
			printStatus(printTime);

			continue;
		}

	}

	printStatus(9999);
}


/////////////Helper functions

System systemSensor(ifstream &infile){
	//add system info

	string tmp;
	int startTime, memory, deviceNum, quantum;

	infile >> tmp;
	startTime = stoi(tmp);
	infile >> tmp;
	memory = stoi(tmp.substr(2));
	infile >> tmp;
	deviceNum = stoi(tmp.substr(2));
	infile >> tmp;
	quantum = stoi(tmp.substr(2));
	QUANTUM = quantum;

	return System(startTime, memory, deviceNum, quantum);
}

Job jobSensor(ifstream &infile){
	//job

	string tmp;
	int arrivalTime, id, memory, maxNeed, runTime, priority;

	infile >> tmp;
	arrivalTime = stoi(tmp);
	infile >> tmp;
	id  = stoi(tmp.substr(2));
	infile >> tmp;
	memory = stoi(tmp.substr(2));
	infile >> tmp;
	maxNeed = stoi(tmp.substr(2));
	infile >> tmp;
	runTime = stoi(tmp.substr(2));
	infile >> tmp;
	priority = stoi(tmp.substr(2));
	return Job(arrivalTime, id, memory, maxNeed, runTime, priority);
}

Request requestSensor(ifstream &infile){
	//request
	string tmp;
	int requestTime, id, deviceNum;
	infile >> tmp;
	requestTime = stoi(tmp);
	infile >> tmp;
	id = stoi(tmp.substr(2));
	infile >> tmp;
	deviceNum = stoi(tmp.substr(2));
	return Request(requestTime, id, deviceNum);
}

Release releaseSensor(ifstream &infile){
	//release

	string tmp;
	int releaseTime, id, deviceNum;
	infile >> tmp;
	releaseTime = stoi(tmp);
	infile >> tmp;
	id = stoi(tmp.substr(2));
	infile >> tmp;
	deviceNum = stoi(tmp.substr(2));
	return  Release(releaseTime, id, deviceNum);
}

#endif /* GENERATOR_HPP_ */
