/*
 * HoldQueue.hpp
 *
 *  Created on: 2018/5/13
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef HOLDQUEUE2_HPP_
#define HOLDQUEUE2_HPP_

#include "readyQueue.hpp"

using namespace std;

class HoldQueue2{
	std::list<Job> q;

public:

	HoldQueue2(){}

	bool empty(){
		return q.empty();
	}

	Job front(){
		return q.front();
	}

	void pop(){
		q.pop_front();
	}

	void print(){
		for(Job job : q) {
			job.print();
		}
	}

	void push(Job in){
		q.push_back(in);
	}
};




#endif /* HOLDQUEUE2_HPP_ */
