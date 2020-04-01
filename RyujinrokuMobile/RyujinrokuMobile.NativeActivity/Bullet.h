//#pragma once
//#include "Drawable.h"
//#include "ImageBullet.h"
//
//class bullet_t {
//public:
//	int counter, counter2, type, color;
//	int id;
//	float a;
//	float x, y;
//	float v, ang, val;
//	float baseX, baseY;
//	float size;
//	float range;
//	bool hit;
//	bool graze;
//	bool isAlive;
//	bool kill;
//	bool keepAlive;
//	bool isAddBlend;
//	bullet_t() {
//		x = y = v = ang = range = val = 0;
//		counter = counter2 = type =  color = id = 0;
//		baseX = baseY = 0;
//		a = 255;
//		size = 1.f;
//		hit = true;
//		graze = true;
//		isAlive = true;
//		keepAlive = false;
//		isAddBlend = false;
//		kill = false;
//	}
//};
//
//class Bullet : public Drawable {
//public:
//	bullet_t dat;
//	Bullet(std::shared_ptr<Context> context, bullet_t* b);
//	~Bullet();
//	bool update() override;
//	void draw() const override;
//};
//
