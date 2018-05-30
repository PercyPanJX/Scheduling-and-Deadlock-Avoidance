/*
 * HoldQueue1.hpp
 *
 *  Created on: 2018/5/13
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef HOLDQUEUE1_HPP_
#define HOLDQUEUE1_HPP_

#include "HoldQueue2.hpp"

class HoldQueue1{
	std::list<Job> q;

public:

	HoldQueue1(){}

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
		for(Job j : q){
			j.print();
		}
	}

	void push(Job in){
		if(q.empty()){
			q.push_back(in);
			return;
		}
		list<Job>::iterator it;
		it = q.begin();
		while(it != q.end()){
			if(in.getRuntime() < it->getRuntime()){
				q.insert(it, in);
				return;
			}
			it++;
		}

		if(in.getRuntime() < it->getRuntime()){
			q.insert(it, in);
			return;
		}

		q.push_back(in);
		return;

	}
};



#endif /* HOLDQUEUE1_HPP_ */
