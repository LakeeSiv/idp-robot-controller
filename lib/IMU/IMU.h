#pragma once
#include <Arduino_LSM6DS3.h>

class RobotIMU {
public:
	float ax, ay, az;
	IMU IMU;
	void ReadAcceleration();
};
