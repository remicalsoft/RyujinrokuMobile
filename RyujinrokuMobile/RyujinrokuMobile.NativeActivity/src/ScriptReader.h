#pragma once

#include "Script.h"
#include <vector>

class ScriptReader
{
public:
	ScriptReader();
	~ScriptReader();
	std::vector<Script>* read(int level, int stage);
};

