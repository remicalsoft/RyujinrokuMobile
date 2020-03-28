#pragma once

#include "Task.h"
#include <DxLib.h>
#include "Image.h"
#include <list>

class EnemyAppearMgr :
	public Task
{
	class Factor : public Task {
		int counter;
		float x, y;
	public:
		Factor(float x, float y) {
			this->x = x;
			this->y = y+128;
			counter = 0;
		}
		bool update() override {
			counter++;
			if (counter == 64) {
				return false;
			}
			y-=2;
			return true;
		}
		void draw() override {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, counter * 6);
			DrawRotaGraph(x,y,1,0,Image::getIns()->enemyAppear,TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	};
	std::list<Factor*> _list;

public:
	EnemyAppearMgr() {

	}
	~EnemyAppearMgr() {
		for (auto f : _list) {
			delete f;
		}
		_list.clear();
	}
	bool update() override {
		for (std::list<Factor*>::iterator it = _list.begin(); it != _list.end();) {
			if ((*it)->update() == false) {
				it = _list.erase(it);
			}
			else {
				it++;
			}
		}
		return true;
	}
	void draw() override {
		for (auto f : _list) {
			f->draw();
		}
	}
	void regist(float x, float y) {
		_list.push_back(new Factor(x, y));
	}
};

