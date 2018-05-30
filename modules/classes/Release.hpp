/*
 * Release.hpp
 *
 *  Created on: May 15, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#ifndef RELEASE_HPP_
#define RELEASE_HPP_

#include "HoldQueue1.hpp"

class Release{
	int releaseTime, id, deviceNum;
public:
	Release();
	Release(int r, int i, int d){
		releaseTime = r;
		id = i;
		deviceNum = d;
	}
	int getReleaseTime(){
		return releaseTime;
	}
	int getID(){
		return id;
	}
	int getDeviceNum(){
		return deviceNum;
	}
};



#endif /* RELEASE_HPP_ */
