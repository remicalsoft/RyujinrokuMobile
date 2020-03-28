#pragma once
#include "Task.h"
#include <DxLib.h>
#include <list>

class Background;
class ShakeTask : public Task {
private:
	Background* bg;
	VECTOR max;
	int shakeFrame;
	int frame;
public:
	ShakeTask(Background* bg, int time, VECTOR max);
	virtual bool update();
};

class Background : public Task
{
protected:
	VECTOR pos;
	VECTOR offset;
	std::list<Task*> activeTask;
	std::list<Task*> finishTask;
public:
	VECTOR getResultPos();
	VECTOR getPos();
	void setPos(VECTOR pos);
	void setOffsetPos(float x, float y, float z);
	void shake(int time, VECTOR power);
	void insertTask(Task* task);
	Background();
	virtual ~Background();
	virtual bool update();
};

