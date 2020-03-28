#include "Parameter.h"
#include <string>

using namespace std;

/*!
@brief パラメータのセット
*/
void Parameter::set(string key, int val)
{
    _map[key] = val;
}

/*!
@brief パラメータの取得
*/
int Parameter::get(string key) const
{
    auto it = _map.find(key);   //指定キーを取得
    if (_map.end() == it) {     //無かったら
        return Error;           //エラー
    }
    else {
        return it->second;      //あったら値を返す
    }
}
