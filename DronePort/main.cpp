#include "components.h"
#include "raylib.h"
#include "vector"

#define SCREEEN_WIDTH 1600
#define SCREEEN_HEIGHT 800

int main() {
	InitWindow(SCREEEN_WIDTH, SCREEEN_HEIGHT, "DronePort");
	SetWindowState(FLAG_VSYNC_HINT);

	LandingZone lz1(200, 200, true, false);
	LandingZone lz2(400, 100, false, true);
	LandingZone lz3(100, 0, true, false);
	std::vector<LandingZone> zones{ lz1, lz2, lz3 };

	Drone drone1(500 + 300, 500 + 300);
	Drone drone2(500 + 300, 500 - 300);
	Drone drone3(500 - 300, 500 + 300);
	Drone drone4(500 - 300, 500 + -300);
	std::vector<Drone> drones{ drone1, drone2, drone3, drone4 };

	Port port1(100, 100, zones);
	std::vector<Port> ports { port1 };

	World world(ports, drones);

	while (!WindowShouldClose()) {


		//Drawing
		BeginDrawing();
		ClearBackground(WHITE);

		world.Draw();
		DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}