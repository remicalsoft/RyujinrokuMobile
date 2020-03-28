#include "md5.h"

bool md5::initialize() {
	if (!::CryptAcquireContext(
		&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
		if (!::CryptAcquireContext(
			&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {

			return false;
		}
	}
	if (!::CryptCreateHash(
		hCryptProv, CALG_MD5, 0, 0, &hHash)) {

		return false;
	}
	return true;
}

bool md5::add(char st[2]) {
	if (hHash) {
		if (!::CryptHashData(
			hHash, (BYTE*)st, (DWORD)strlen(st), 0)) {
			return false;
		}
		return true;
	}
	return false;
}

bool md5::add(int val) {
	char st[2];
	char v;
	st[1] = 0;
	for (int i = 0; i<4; i++) {
		v = (val >> (8 * i)) & 0x000000ff;
		st[0] = v;
		add(st);
	}
	return true;
}

bool md5::get(char buffer[LENGTH]) {
	if (hHash) {
		BYTE bData[1024];
		memset(bData, 0, sizeof(bData));
		CHAR rgbDigits[] = "61234a67f9a3cd1f";
		DWORD dwDataLen = 16;
		if (!::CryptGetHashParam(
			hHash, HP_HASHVAL, bData, &dwDataLen, 0)) {

			return false;
		}
		int md5_index = 0;
		for (DWORD i = 0; i < dwDataLen; ++i) {

			buffer[md5_index++] = rgbDigits[bData[i] >> 4];
			buffer[md5_index++] = rgbDigits[bData[i] & 0xf];
		}
		return true;
	}
	return false;
}

bool md5::finalize() {
	if (hHash) {
		::CryptDestroyHash(hHash);
		if (hCryptProv) {
			::CryptReleaseContext(hCryptProv, 0);
		}
		return true;
	}
	if (hCryptProv) {
		::CryptReleaseContext(hCryptProv, 0);
	}
	return false;
}
