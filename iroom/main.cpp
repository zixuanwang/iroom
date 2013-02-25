#include "Room.h"

int main(int argc, char* argv[]){
	std::string config_path = "c:/users/zixuan/desktop/config.dat";
	int duration = 10;
	std::string output_dir = "c:/users/zixuan/desktop/iroom";
	if(argc == 1){
		std::cout << "usage: ./iroom -config c:/config.dat -duration 10 -dir c:/users/zixuan/desktop/iroom" << std::endl;
	}else{
		for(int i = 1; i < argc; ++i){
			if(!strcmp(&argv[i][1], "config")){
				config_path = argv[i+1];
			}
			if(!strcmp(&argv[i][1], "duration")){
				duration = atoi(argv[i+1]);
			}
			if(!strcmp(&argv[i][1], "dir")){
				output_dir = argv[i+1];
			}
		}
	}
	Room room;
	room.init(config_path);
	room.capture(output_dir, duration);
	return 0;
}