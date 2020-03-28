#pragma once

#include "Task.h"
#include "ISceneChangedListener.h"

class ISceneChangedListener;

class Scene : public Task
{
protected:
	ISceneChangedListener* _implSceneChanged;
public:
	Scene(ISceneChangedListener *impl);
	~Scene();
};

