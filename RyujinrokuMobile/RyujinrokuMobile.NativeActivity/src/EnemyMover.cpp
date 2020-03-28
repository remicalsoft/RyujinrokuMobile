#include "EnemyMover.h"
#include "Define.h"
#include <math.h>

using namespace std;

//下に降りる。しばらくすると止まり、また下に降りる
void EnemyMove00(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	int wait = enemy->_script.waitTime;
	if (0 == cnt) {
		enemy->_angle = PI / 2;
		enemy->_v = 3;
	}
	if (60 < cnt && cnt < 90) {
		enemy->_v -= 0.1;
	}
	if (90 + wait < cnt && cnt < 90 + wait + 30) {
		enemy->_v += 0.1;
	}
}

//左下へ
void EnemyMove01(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = PI * 3 / 4;
		enemy->_v = 4;
	}
}

//右下へ
void EnemyMove02(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = PI * 1 / 4;
		enemy->_v = 4;
	}
}

//左INで回転して左へ
void EnemyMove03(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = PI;
		enemy->_v = 6;
	}
	if (75 <= cnt && cnt < 75 + 60) {
		enemy->_angle -= PI * 2 / 60;
	}
}

//⇒INで回転して左へ
void EnemyMove04(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = 0;
		enemy->_v = 6;
	}
	if (75 <= cnt && cnt < 75 + 60) {
		enemy->_angle += PI * 2 / 60;
	}
}

//下にずっと降りる
void EnemyMove05(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = PI/2;
		enemy->_v = 3;
	}
}

//waitTime停滞して上に行く
void EnemyMove06(std::shared_ptr<Enemy> enemy)
{
	int wait = enemy->_script.waitTime;
	int cnt = enemy->_counter;
	if (cnt == 0) {
		enemy->_angle = PI / 2;
	}
	if (cnt == wait) {
		enemy->_angle = -PI/2;
		enemy->_v = 2;
	}
}

//高速左INで回転して左へ
void EnemyMove07(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = PI;
		enemy->_v = 12;
	}
	if (32 <= cnt && cnt < 32 + 30) {
		enemy->_angle -= PI * 2 / 30;
	}
}

//高速右INで回転して左へ
void EnemyMove08(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	if (0 == cnt) {
		enemy->_angle = 0;
		enemy->_v = 12;
	}
	if (32 <= cnt && cnt < 32 + 30) {
		enemy->_angle += PI * 2 / 30;
	}
}

//突如出現。しばらくして上に
void EnemyMove09(std::shared_ptr<Enemy> enemy)
{
	int cnt = enemy->_counter;
	int wait = enemy->_script.waitTime;
	if (cnt > wait) {
		enemy->_angle = -PI / 2;
		enemy->_v += 0.1;
	}
}

EnemyMover::EnemyMover()
{
	_list.push_back(EnemyMove00);
	_list.push_back(EnemyMove01);
	_list.push_back(EnemyMove02);
	_list.push_back(EnemyMove03);
	_list.push_back(EnemyMove04);
	_list.push_back(EnemyMove05);
	_list.push_back(EnemyMove06);
	_list.push_back(EnemyMove07);
	_list.push_back(EnemyMove08);
	_list.push_back(EnemyMove09);
}

void EnemyMover::update(std::shared_ptr<Enemy> enemy, int id)
{
	if (id >= _list.size()) {
		return;
	}
	_list[id](enemy);
	enemy->_x += cos(enemy->_angle)*enemy->_v;
	enemy->_y += sin(enemy->_angle)*enemy->_v;
	if (enemy->_isNotAppearedYet) { //まだ画面内に出現していない
		if (0 <= enemy->_x && enemy->_x <= OUT_W && 0 <= enemy->_y && enemy->_y <= OUT_H) {//出現した
			enemy->_isNotAppearedYet = false;
		}
	}
	else {
		if (-enemy->_imgSizeW / 2 <= enemy->_x && enemy->_x <= OUT_W + enemy->_imgSizeW / 2
			&& -enemy->_imgSizeH / 2 <= enemy->_y && enemy->_y <= OUT_H + enemy->_imgSizeH / 2) {
			//nothing
		}
		else {
			enemy->_isAlive = false;
		}
	}
}
