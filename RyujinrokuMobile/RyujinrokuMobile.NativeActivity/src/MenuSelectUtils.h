#pragma once
class MenuSelectUtils
{
public:
	MenuSelectUtils();
	~MenuSelectUtils();
	static bool canSelectPracticeStage(int level, int stage);
	static bool canSelectEXStage(int level);
	static bool canSelectPHStage(int level);
	static bool isClearStage(int stage);
	static bool havePlayed(int stage);
};

