#include "PlayerShot.h"
#include <math.h>

const static float V = 50;

PlayerShot::PlayerShot(float x, float y, float power){
	_x = x;
	_y = y;
	_power = power;
}

PlayerShot::~PlayerShot(){
}

bool PlayerShot::update(){
	_x += cos(_angle)*_v;
	_y += sin(_angle)*_v;
	return false;
}

void PlayerShot::draw(){
}
