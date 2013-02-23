#include "Room.h"

int main(int argc, char* argv[]){
	Room room;
	room.init("c:/users/zixuan/desktop/config.dat");
	room.capture("c:/users/zixuan/desktop");
	//Camera cam("171.67.88.34", "WSNLCAM", "y2e2cam");
	//cam.capture("c:/users/zixuan/desktop/frame.dat", "c:/users/zixuan/desktop/timestamp.dat");
	return 0;
}