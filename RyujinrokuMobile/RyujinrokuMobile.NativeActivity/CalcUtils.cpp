#include "CalcUtils.h"
#include <math.h>
#include <DxLib.h>

/*
*@brief valの小数点第point位を四捨五入して丸める
*/
float CalcUtils::roundPoint(float val, int point) {
    float ret;
    ret = val * pow(10.f, + point - 1);
    ret = (float)(int)(ret + 0.5f);
    return ret * pow(10.f, - point + 1);
}
