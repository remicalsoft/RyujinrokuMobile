#pragma once

class ShineLine {
protected:
	float _x1, _y1, _x2, _y2;
	float _angle, _v;
	int _alfa;
	int _counter;
	bool _isEndMove, _isStartMove;
	int _color;
public:
	ShineLine(float x, float y){
		_x1 = _x2 = x;
		_y1 = _y2 = y;
	}
	virtual ~ShineLine(){}
	virtual bool update(){
		return true;
	}
	virtual void draw();
};
