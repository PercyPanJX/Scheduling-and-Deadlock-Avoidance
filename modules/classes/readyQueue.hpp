/*
 * mainQueue.hpp
 *
 *  Created on: 2018-5-18
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef READYQUEUE_HPP_
#define READYQUEUE_HPP_


#include "System.hpp"

class readyQueue{
	std::list<Job> q;

public:
	readyQueue(){};
	void push(Job job){
		q.push_back(job);
	}
	void pop(){
		q.pop_front();
	}
	Job front(){
		return q.front();
	}
	bool empty(){
		return q.empty();
	}
	int size() {
		return q.size();
	}
	void print() {
		for(Job job : q) {
			job.print();
			cout << endl;
		}
	}
};


#endif /* READYQUEUE_HPP_ */
