#pragma once
#include "Background.h"
#include "SpriteRenderer.h"
#include"tinyxml2.h"
#include<list>
#include<vector>

class SpriteRenderer;
class Camera;

class Background02 : public Background {
private:
	class MapModelTask : public Task {
	private:
		std::vector<int> imgHandle;
		std::vector<SpriteRenderer*> objList;
		std::vector<VECTOR> objPosList;
		VECTOR pos;
		VECTOR offset;
	public:
		MapModelTask(std::vector<int> imgHandle, tinyxml2::XMLElement* root, VECTOR pos);
		~MapModelTask();
		void setOffset(VECTOR ofs);
		virtual bool update() override;
		virtual void draw() override;
	};
private:
	std::list<MapModelTask*> tasklist;
	std::vector<int> imgHandle;
	Camera* camera;
public:
	Background02();
	~Background02();
	bool update() override;
	void draw() override;
};
