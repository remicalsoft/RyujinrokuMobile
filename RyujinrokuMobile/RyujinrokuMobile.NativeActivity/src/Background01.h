#pragma once
#include"Background.h"
#include"Task.h"
#include"tinyxml2.h"
#include<list>

class SpriteRenderer;
class Camera;

class Background01 : public Background {
private:
	class MapModelTask : public Task {
	private:
		enum Constants {
			WOOD_COUNT = 40,
		};
		VECTOR pos;
		VECTOR offset;
		SpriteRenderer* floor;
		SpriteRenderer* wood;
		VECTOR poslist[WOOD_COUNT];
		int currentEdit;
	public:
		void saveXml(tinyxml2::XMLDocument& doc);
		void loadXml(tinyxml2::XMLElement* root);
		MapModelTask(int grFloor, int grWood1, tinyxml2::XMLElement* root, VECTOR pos);
		~MapModelTask();
		void setOffset(VECTOR ofs);
		virtual bool update() override;
		virtual void draw() override;
		void drawFloor();
		void drawWood();
	};
private:
	Camera* camera;
	std::list<MapModelTask*> tasklist;
	int handle1;
	int handle2;
	int handle3;
	int handle4;
	int handle5;
	int count;
public:
	Background01();
	~Background01();
	bool update() override;
	void draw() override;
};
