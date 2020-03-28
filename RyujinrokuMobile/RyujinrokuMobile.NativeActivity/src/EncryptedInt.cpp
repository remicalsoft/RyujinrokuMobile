#include "EncryptedInt.h"
#include <DxLib.h>
#include "Define.h"

const static int KEY  = 0x3B25'2A19'26C3'465E; //XOR暗号キー
const static int HASH = 0xB63A'9461'CC31'183F; //ハッシュキー

EncryptedInt::EncryptedInt()
{
	value = new int;
	*value = 0 ^ KEY;
	hashValue = 0 ^ HASH;
}

EncryptedInt::~EncryptedInt()
{
	delete value;
}

/*!
 * brief 改竄チェック
 * ハッシュ値と異なっていたら改竄されたとする
 */
bool EncryptedInt::isTampered()
{
	if (*value ^ KEY == hashValue ^ HASH) {
		return false;
	}
	else {
		return true;
	}
}

/*!
* @brief 値をセットする
* セットするたびに格納先のアドレスを変える。
* ただ新しくnewするだけだと連続する可能性があるのでランダムに無駄にnewを繰り返した上で作成する
* @param(in) value セットする値
* @retval 現在の値
*/
void EncryptedInt::set(int v)
{
	if (isTampered()) {
		ERR("不正ツールによる改竄が検出されたため終了します");
	}

	int n = GetRand(3000); //適当にnew繰り返す分
	int** pool = new int*[n];

	int tmp = *value;

	for (int i = 0; i<n; i++) {
		pool[i] = new int;
	}

	delete value;
	value = new int;
	*value = v ^ KEY;
	hashValue = v ^ HASH;

	for (int i = 0; i<n; i++) {
		delete pool[i];
	}
	delete[] pool;
}

int EncryptedInt::get()
{
	if (isTampered()) {
		ERR("不正ツールによる改竄が検出されたため終了します");
	}
	return (*value) ^ KEY;
}

