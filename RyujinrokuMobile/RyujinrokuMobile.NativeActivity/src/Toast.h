#pragma once
#include "Singleton.h"
#include <list>
#include <string>

class Toast : public Singleton<Toast>
{
	int _counter;
	int _font;
	std::list<std::string*> _list;
public:
	Toast();
	~Toast();
	void update();
	void draw();
	void add(const char* msg);
	void add(std::string msg);
};
