/*
 * CompletedQueue.hpp
 *
 *  Created on:
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef COMPLETEDQUEUE_HPP_
#define COMPLETEDQUEUE_HPP_

#include "Job.hpp"


class CompletedQueue{
	std::list<Job> q;

public:
	CompletedQueue(){};
	void push(Job job){
		q.push_back(job);
	}
	void print(){
		for(Job job : q) {
			job.print();
		}
	}
};





#endif /* COMPLETEDQUEUE_HPP_ */
