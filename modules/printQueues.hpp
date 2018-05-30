/*
 * printQueues.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef PRINTQUEUES_HPP_
#define PRINTQUEUES_HPP_

#include "bankAlgorithm.hpp"

void printQueues() {

	cout << "\n===============================================\n" << endl;
	output << "\n===============================================\n" << endl;

	cout << "----- Current Time: " << currentTime << " -----"<< endl;
	output << "----- Current Time: " << currentTime << " -----"<< endl;

	cout << "******** System Infomation *********" <<endl;
	output << "******** System Infomation *********" <<endl;
	sys.print();

	cout << "******** Hold Queue 1 ********" << endl;
	output << "******** Hold Queue 1 ********" << endl;
	HQ1.print();

	cout << "******** Hold Queue 2 ********" << endl;
	output << "******** Hold Queue 2 ********" << endl;
	HQ2.print();


	cout << "******** Ready Queue ********" << endl;
	output << "******** Ready Queue ********" << endl;

	RQ.print();
	cout << "******** Wait Queue ********" << endl;
	output << "******** Wait Queue ********" << endl;
	queue<Job> tmpWQ = WQ;

	for(int i = 0; i < tmpWQ.size(); i++) {
		tmpWQ.front().print();
		tmpWQ.pop();
	}

	cout << "******** Completed Queue ********" << endl;
	output << "******** Completed Queue ********" << endl;
	CQ.print();

	cout << "******** CPU Running ********"<< endl;
	output << "******** CPU Running ********"<< endl;
	if(!sys.getIdle()){
		sys.getCurrentJob().print();
	}

}


#endif /* PRINTQUEUES_HPP_ */
