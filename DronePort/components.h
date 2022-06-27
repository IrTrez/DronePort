#pragma once

#include <vector>

class LandingZone {
private:
public:
	int x;
	int y;
	int land;
	int takeoff;

	int ID = -1;

	int zoneType;

	int absx;
	int absy;
	
	LandingZone();
	LandingZone(int ax, int ay, bool aland = true, bool atakeoff = false);
	void Draw();

};


class Port {
public:
	int x;
	int y;
	int ID = -1;
	int numPorts;

	int RSOI = 500;

	std::vector<LandingZone> zones;

	Port();
	Port(int ax, int ay, std::vector<LandingZone> azones);
	void Draw();
};

class Drone;


class World {
public:
	int epoch = 0;
	std::vector<Port> ports;
	std::vector<Drone> drones;

	World();
	World(std::vector<Port> aports, std::vector<Drone> adrones);
	void Draw();
	void Propagate();
};


class Drone
{
public:
	float x;
	float y;
	float maxSpeed{ 20.0f };

	float xx{ 0 };
	float yy{ 0 };
	
	float heading{ 0 };
	
	int ID{ -1 };
	int droneSize = 25;

	World world;
	Port nearestPort;
	LandingZone nearestLZ;
	
	Drone(float ax, float ay);
	void getNearestLandingPort();
	void Draw();
	void Propagate();
};

