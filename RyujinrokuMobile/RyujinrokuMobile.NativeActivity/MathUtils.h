#pragma once

float randf ( float val );
float randf2( float val );

class MathUtils {
public:
	static float getAngle(float srcX, float srcY, float dstX, float dstY);
	static float roundPoint(float val, int point);
};