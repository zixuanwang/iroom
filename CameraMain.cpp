/*
 * CameraMain.cpp
 *
 *  Created on: Apr 1, 2013
 *      Author: zxwang
 */
#include "Camera.h"

int main(int argc, char* argv[]){
	if(argc == 1){
		std::cout << "Usage: ./camera ip-address username password seconds output-dir" << std::endl;
		return 0;
	}
	Camera camera(argv[1], argv[2], argv[3]);
	std::stringstream ss;
	ss << argv[5] << "/" << argv[1];
	camera.capture(ss.str() + ".avi", ss.str() + ".timestamp", atoi(argv[4]));
	return 0;
}



