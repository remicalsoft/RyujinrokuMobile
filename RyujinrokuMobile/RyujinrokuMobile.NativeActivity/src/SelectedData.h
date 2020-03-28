#pragma once
class SelectedData
{
public:
	SelectedData();
	~SelectedData();
	static int read();
	static void save(int level);
};

