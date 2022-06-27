#include "raylib.h"
#include "components.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <numeric>


LandingZone::LandingZone() {
	x = 0;
	y = 0;
	land = false;
	takeoff = false;
	zoneType = (land) ? 1 : 0;
	absx = x;
	absy = y;
}


LandingZone::LandingZone(int ax, int ay, bool aland, bool atakeoff) {
	x = ax;
	y = ay;
	land = aland;
	takeoff = atakeoff;


	zoneType = (land) ? 1 : 0;

	absx = x;
	absy = y;
}

void LandingZone::Draw() {
	DrawRectangle(absx, absy, 50, 50, zoneType ? GREEN : RED);
}


Port::Port() {
	x = 0;
	y = 0;
	zones = std::vector<LandingZone>{};
}


Port::Port(int ax, int ay, std::vector<LandingZone> azones) {
	zones = azones;
	
	x = ax;
	y = ay;

	size_t numZones = zones.size();

	for (int idx = 0; idx < numZones; idx++) {
		zones[idx].ID = idx;
		zones[idx].absx = zones[idx].x + x;
		zones[idx].absy = zones[idx].y + y;
	}
}


void Port::Draw() {
	for (auto & i : zones) {
		i.Draw();
	}
}


World::World(){
	ports = std::vector<Port>{};
	drones = std::vector<Drone>{};
}


World::World(std::vector<Port> aports, std::vector<Drone> adrones)
{
	ports = aports;
	drones = adrones;
	size_t numPorts = ports.size();
	size_t numDrones = drones.size();

	for (int idx = 0; idx < numPorts; idx++)
	{
		ports[idx].ID = idx;
	}

	for (int idx = 0; idx < numDrones; idx++)
	{
		drones[idx].ID = idx;
		drones[idx].world = *this;
		drones[idx].getNearestLandingPort();
	}
}

void World::Draw() {
	for (auto& drone : drones) {
		drone.Draw();
	}
	for (auto& port : ports) {
		port.Draw();
	}
	
}

void World::Propagate() {
	std::cout << "hi";
}

Drone::Drone(float ax, float ay) {
	x = ax;
	y = ay;

	Drone::getNearestLandingPort();
}

void Drone::getNearestLandingPort() {
	double nearestDistance = 100000.0f;
	Port tempPort = nearestPort;
	LandingZone tempLZ = nearestLZ;


	for (auto& port : world.ports) {
		for (auto& zone : port.zones) {
			double distance = std::pow((zone.absx - x),2) + std::pow((zone.absy - y), 2);
			if ((distance < nearestDistance) && (zone.land)) {
				nearestDistance = distance;
				tempLZ = zone;
				tempPort = port;
			}
		}
	}

	nearestPort = tempPort;
	nearestLZ = tempLZ;
}


void Drone::Draw() {
	DrawCircle(static_cast<int>(x), static_cast<int>(y), droneSize, DARKBLUE);
}

void Drone::Propagate() {
	//float vectorP[2] = { nearestLZ.absx, nearestLZ.absy};
	//float vectorD[2] = {x, y};

	float vec[2] = { nearestLZ.absx - x , nearestLZ.absy - y };

	// Rule 1 fly to LZ
	xx = vec / std::pow(std::inner_product(vec, vec), 0.5) * maxpeed/2


	// Limit speed
	float speed = std::pow((std::pow(xx, 2) + std::pow(yy, 2)), 2);
	xx = (speed > maxSpeed) ? xx * (maxSpeed / speed) : xx;
	yy = (speed > maxSpeed) ? yy * (maxSpeed / speed) : yy;


	x += xx;
	y += yy;
}