#include "StartLevel.h"



StartLevel::StartLevel()
{
}


StartLevel::~StartLevel()
{
}

void StartLevel::Load() {
	y = ySpeed = 0.0f;
}

void StartLevel::Unload() {

}


void StartLevel::Update() {
	ySpeed += 1.0f;
	y += ySpeed;

	if (y > 600) {
		y = 600;
		ySpeed = -30.0f;
	}
}


void StartLevel::Render() {
	//HXGAME->graphics->DrawCircle(100, y, 50, 1.0, 1.0, 1.0, 1.0);
}