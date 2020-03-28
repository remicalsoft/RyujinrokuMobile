#pragma once

#include <DxLib.h>

typedef enum{
	eSRF00_WIND,
	eSRF00_FLOR,
	eSRF00_DOOR,
	eSRF00_LOOF,
	eSRF00_DATANUM,
}eSRF00;

typedef enum {
	eSRF01_WOOD,
	eSRF01_DATANUM,
}eSRF01;


class Srf{

	VERTEX3D	_vertex[ 4 ] ;
	WORD		_index[ 6 ] ;
	int			_handle;
	VECTOR		_angle;

public:
	Srf( int z, int sHdl, unsigned uType );
	bool update();
	void draw(VECTOR offset);

	float getZ();
	float getZWid();
	void addZ( float fZ );
};
