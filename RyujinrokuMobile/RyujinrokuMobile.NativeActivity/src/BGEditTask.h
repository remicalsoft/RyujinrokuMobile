#pragma once

#include<list>
#include"Task.h"


class BGEditTask : public Task {
private:
	std::list<Task> task;
public:
	virtual bool update() override;
	virtual void draw() override;
};

