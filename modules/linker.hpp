/*
 * linker.hpp
 *
 *  Created on: May 18, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef MODULES_LINKER_HPP_
#define MODULES_LINKER_HPP_


#include "./classes/Request.hpp"

int QUANTUM;
int currentTime;
HoldQueue1 HQ1;
HoldQueue2 HQ2;
readyQueue RQ;
queue<Job> WQ;
CompletedQueue CQ;
System sys;
queue<int> printTimes;


#endif /* MODULES_LINKER_HPP_ */
