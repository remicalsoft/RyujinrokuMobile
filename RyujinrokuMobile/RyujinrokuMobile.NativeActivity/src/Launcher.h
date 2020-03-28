#pragma once
#include "Task.h"

#define LAUNCHER_LIGHT_DRAWNUM 4

enum eLauncherType {
	eLauncherType_Normal,
	eLauncherType_Hanabi,
};

class Launcher :
	public Task
{
public:
	enum eLauncherType _type;
	int img;
	float x, y;
	float v, ang;
	float firstX, firstY, moveX, moveY;
	float _a[LAUNCHER_LIGHT_DRAWNUM];
	float _s[LAUNCHER_LIGHT_DRAWNUM];
	int id;
	int counter;
	bool isShooting;
	int shotCounter;
	static const int TIME = 30;
	Launcher(float x, float y, int img);
	Launcher(float firstX, float firstY, float moveX, float moveY, int img);
	Launcher(float firstX, float firstY, float moveX, float moveY, eLauncherType type);
	~Launcher();
	void init(float x, float y, int img);
	bool update() override;
	void draw() override;
};
