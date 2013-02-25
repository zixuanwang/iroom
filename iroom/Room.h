#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include "Camera.h"

class Room
{
public:
	Room(void);
	virtual ~Room(void);
	// load configuration from the file.
	// the first line of the configuration file is username. the second line is password.
	// the rest lines are ip addresses.
	void init(const std::string& config_path);
	// start capturing. output_dir is the folder to save frames and timestamps.
	void capture(const std::string& output_dir, int n); // capture the video for n seconds. video files and timestamps are saved into output_dir.
private:
	std::vector<std::shared_ptr<Camera> > m_camera_array;
};

