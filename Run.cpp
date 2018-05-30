/*
 * Run.cpp
 *
 *  Created on: May 14, 2018
 *      Author: Qun Cheng
 *      Author: Jiaxuan(Percy) Pan
 */

#include "./modules/generator.hpp"

int main(){
	ifstream infile;
	infile.open("input.txt");
	output.open("output.txt");
	generator(infile);
	infile.close();
	output.close();
	return 0;
}
