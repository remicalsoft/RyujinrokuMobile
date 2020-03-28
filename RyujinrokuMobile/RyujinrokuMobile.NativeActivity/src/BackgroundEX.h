#pragma once
#include "Background.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "tinyxml2.h"
#include <list>


class BackgroundEX : public Background {
private:
	class MapModelTask : public Task {
	private:
		std::vector<int> imgHandle;
		std::vector<int> modelHandle;
		std::vector<Object*> objList;
		std::vector<VECTOR> objPosList;
		VECTOR pos;
		VECTOR offset;
	public:
		MapModelTask(std::vector<int> imgHandle, std::vector<int> modelHandle, tinyxml2::XMLElement* root, VECTOR pos);
		~MapModelTask();
		void setOffset(VECTOR ofs);
		virtual bool update() override;
		virtual void draw() override;
	};
private:
	std::list<MapModelTask*> tasklist;
	std::vector<int> imgHandle;
	std::vector<int> modelHandle;
	Camera* camera;

	VECTOR defaultPos;
	VECTOR defaultCenter;
	float defaultV;
	float defaultH;
	float defaultT;
	int count;

private:
public:
	BackgroundEX();
	~BackgroundEX();
	bool update() override;
	void draw() override;
};
