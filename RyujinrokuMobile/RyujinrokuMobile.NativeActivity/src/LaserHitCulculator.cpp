#include "LaserHitCulculator.h"
#include <math.h>
#include "Define.h"

using namespace std;

LaserHitCulculator::LaserHitCulculator()
{
}


LaserHitCulculator::~LaserHitCulculator()
{
}

/* ２次元ベクトル */
typedef struct {
	float x, y;
} Vector_t;

/* diff ← ベクトル p - q */
void Vector2Diff(Vector_t *diff, const Vector_t *p, const Vector_t *q) {
	diff->x = p->x - q->x;
	diff->y = p->y - q->y;
}

/* ベクトル p と q の内積 */
float Vector2InnerProduct(const Vector_t *p, const Vector_t *q) {
	return p->x * q->x + p->y * q->y;
}

/* ベクトル p と q の外積 */
float Vector2OuterProduct(const Vector_t *p, const Vector_t *q) {
	return p->x * q->y - p->y * q->x;
}

//点と線分との距離を求める
float getLengthLineAndPt(float x, float y, float x1, float y1,
	float x2, float y2) {
	float dx, dy, a, b, t, tx, ty;
	float distance;
	dx = (x2 - x1); dy = (y2 - y1);
	a = dx*dx + dy*dy;
	b = dx * (x1 - x) + dy * (y1 - y);
	t = -b / a;
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	tx = x1 + dx * t;
	ty = y1 + dy * t;
	distance = sqrt((x - tx)*(x - tx) + (y - ty)*(y - ty));
	return distance;
}

//点と点との距離を返す
float getLength(pt_t p1, pt_t p2) {
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

//点が円の中にあるかどうか。0:なし　1:あり
float exitsInsideCircle(pt_t p, pt_t rp, float r) {
	float dx = p.x - rp.x, dy = p.y - rp.y;
	if (dx*dx + dy*dy < r*r)    return 1;
	else                    return 0;
}

//入れ替え
void swap(float *n, float *m) {
	float t = *m;
	*m = *n; *n = t;
}

//３点から角度を返す
float getAngle(pt_t pt0, pt_t pt1, pt_t rpt) {
	/* ベクトル C→P と C→Q のなす角θおよび回転方向を求める．*/
	Vector_t c, p, q; /* 入力データ */
	Vector_t cp;      /* ベクトル C→P */
	Vector_t cq;      /* ベクトル C→Q */
	float s;          /* 外積：(C→P) × (C→Q) */
	float t;          /* 内積：(C→P) ・ (C→Q) */
	float theta;      /* θ (ラジアン) */

					  /* c，p，q を所望の値に設定する．*/
	c.x = pt0.x;    c.y = pt0.y;
	p.x = pt1.x;    p.y = pt1.y;
	q.x = rpt.x;    q.y = rpt.y;

	/* 回転方向および角度θを計算する．*/
	Vector2Diff(&cp, &p, &c);          /* cp ← p - c   */
	Vector2Diff(&cq, &q, &c);          /* cq ← q - c   */
	s = Vector2OuterProduct(&cp, &cq); /* s ← cp × cq */
	t = Vector2InnerProduct(&cp, &cq); /* t ← cp ・ cq */
	theta = atan2(s, t);
	return theta;
}

//長方形と円との当たりを判定する
bool isHitBoxAndCircle(pt_t pt[4], pt_t playerPt, float r) {
	int i;
	float x = playerPt.x, y = playerPt.y;
	float theta, theta2;

	/*円の中に長方形の４点のうちどれかがあるかどうか判定*/
	for (i = 0; i<4; i++) {
		if (exitsInsideCircle(pt[i], playerPt, r) == 1)
			return true;
	}
	/*ここまで*/

	/*長方形の中に物体が入り込んでいるかどうかを判定判定*/

	theta  = getAngle(pt[0], pt[1], playerPt);//3点の成す角1
	theta2 = getAngle(pt[2], pt[3], playerPt);//3点の成す角2

	if (0 <= theta && theta <= PI / 2 && 0 <= theta2 && theta2 <= PI / 2) {
		return true;
	}

	/*ここまで*/

	/*線分と点との距離を求める*/
	for (i = 0; i<4; i++) {
		if (getLengthLineAndPt(playerPt.x, playerPt.y, pt[i].x, pt[i].y, pt[(i + 1) % 4].x, pt[(i + 1) % 4].y) < r) {
			return true;
		}
	}
	/*ここまで*/
	return false;//どこにもヒットしなかったらぶつかっていない
}

bool LaserHitCulculator::itHit(std::list<Laser*>* laserList, Player * player)
{
	pt_t sqrp[4], playerPt( player->getX(), player->getY());//長方形の4点と円の中心
									  //レーザー分ループ
	for (auto l : *laserList) {
		//レーザーが登録されていて、当たり判定をする設定なら
		if (l->hitWidth != 0) {
			for (int i = 0; i<4; i++) {//レーザーの4点を設定
				sqrp[i].x = l->outpt[i].x;
				sqrp[i].y = l->outpt[i].y;
			}
			//長方形と円との接触判定
			if (isHitBoxAndCircle(sqrp, playerPt, player->getHitRange())) {
				return true;
			}
		}
	}
	return false;
}
