#include "Background.h"


ShakeTask::ShakeTask(Background* bg, int time, VECTOR max) {
	this->bg = bg;
	this->max = max;
	this->shakeFrame = time;
	this->frame = 0;
}

// virtual
bool ShakeTask::update() {
	if (this->frame >= this->shakeFrame) {
		this->bg->setOffsetPos(0, 0, 0);
		return false;
	}
	float maxX = this->max.x;
	float maxY = this->max.y;
	float maxZ = this->max.z;
	float f = this->frame;
	float t = this->shakeFrame;
	float fx = maxX - (maxX * (f / t));
	float fy = maxY - (maxY * (f / t));
	float fz = maxZ - (maxZ * (f / t));
	int x = fx;
	int y = fy;
	int z = fz;
	if (x <= 0) { x = 1; }
	if (y <= 0) { y = 1; }
	if (z <= 0) { z = 1; }
	int randX = rand();
	int randY = rand();
	int randZ = rand();
	this->bg->setOffsetPos(randX % x, randY % y, randZ % z);
	this->frame++;
	return true;
}


VECTOR Background::getResultPos() {
	return VGet(
		this->pos.x + this->offset.x,
		this->pos.y + this->offset.y,
		this->pos.z + this->offset.z);
}

VECTOR Background::getPos() {
	return this->pos;
}

void Background::setPos(VECTOR pos) {
	this->pos = pos;
}

void Background::setOffsetPos(float x, float y, float z) {
	this->offset = VGet(x, y, z);
}

void Background::shake(int time, VECTOR power) {
	this->insertTask(new ShakeTask(this, time, power));
}

void Background::insertTask(Task* task) {
	this->activeTask.push_back(task);
}

Background::Background(){
	this->pos = VGet(0, 0, 0);
	this->offset = VGet(0, 0, 0);
}

Background::~Background(){
	while (this->activeTask.size() > 0) {
		auto task = this->activeTask.front();
		this->activeTask.remove(task);
		delete task;
	}
}

// virtual
bool Background::update() {
	for (auto task : this->activeTask) {
		bool active = task->update();
		if (!active) {
			this->finishTask.push_back(task);
		}
	}
	while (this->finishTask.size() > 0) {
		auto task = this->finishTask.front();
		this->activeTask.remove(task);
		this->finishTask.remove(task);
		delete task;
	}
	return true;
}

