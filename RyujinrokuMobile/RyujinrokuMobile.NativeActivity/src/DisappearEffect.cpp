#include "DisappearEffect.h"

using namespace std;

bool DisappearEffect::update(){
	_counter++;
	if (_counter < 4 && _counter%1 == 0) {
		_list.push_back(new Disappear(_x,_y));
	}
	for (list<Disappear*>::iterator it = _list.begin(); it != _list.end();) {
		if ((*it)->update() == false) {
			delete (*it);
			it = _list.erase(it);
		}
		else {
			it++;
		}
	}
	if (_list.size() == 0) {
		return false;
	}
	return true;
}

void DisappearEffect::draw(){
	for (auto e : _list) {
		e->draw();
	}
}
