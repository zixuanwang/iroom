#include "Room.h"

int main(int argc, char* argv[]){
	Room room;
	room.init("c:/users/zixuan/desktop/config.dat");
	room.capture("c:/users/zixuan/desktop");
	return 0;
}