#pragma once
#include "Enemy.h"
#include <vector>

#include "Singleton.h"

class EnemyMover : public Singleton<EnemyMover> {

	EnemyMover();
	friend Singleton<EnemyMover>;

	typedef void(*FUNC)(std::shared_ptr<Enemy>);
	std::vector<FUNC> _list;

public:
	void update(std::shared_ptr<Enemy>, int id);

};
