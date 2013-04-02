/*
 * iRoomMain.cpp
 *
 *  Created on: Apr 1, 2013
 *      Author: zxwang
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::string username;
std::string password;
std::vector<std::string> ip_address_vector;

void load_config(const std::string& config_path){
	std::ifstream in_stream;
	in_stream.open(config_path);
	if(in_stream.good()){
		// read username and password
		getline(in_stream, username);
		getline(in_stream, password);
		// read ip_address
		std::string ip_address;
		while(getline(in_stream, ip_address)){
			ip_address_vector.push_back(ip_address);
		}
		in_stream.close();
	}
}

int main(int argc, char* argv[]){
	if(argc == 1){
		std::cout << "Usage: ./iroom config.dat seconds output-dir" << std::endl;
		return 0;
	}
	load_config(argv[1]);
	for(size_t i = 0; i < ip_address_vector.size(); ++i){
		std::string cmd = "./camera " + ip_address_vector[i] + " " + username + " " + password + " " + argv[2] + " " + argv[3] + " &";
		std::cout << cmd.c_str() << std::endl;
		system(cmd.c_str());
	}
	return 0;
}


