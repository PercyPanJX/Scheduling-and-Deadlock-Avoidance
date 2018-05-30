/*
 * Request.hpp
 *
 *  Created on: May 15, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "Release.hpp"

class Request{
	int requestTime, id, deviceNum;
public:
	Request();
	Request(int r, int i, int d){
		requestTime = r;
		id = i;
		deviceNum = d;
	}
	int getRequestTime(){
		return requestTime;
	}

	int getID(){
		return id;
	}

	int getDeviceNum(){
		return deviceNum;
	}
};




#endif /* REQUEST_HPP_ */
