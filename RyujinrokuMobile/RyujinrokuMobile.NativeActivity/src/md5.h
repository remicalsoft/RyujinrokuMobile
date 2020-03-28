#pragma once

#include <windows.h>
#include <wincrypt.h>
#include <iostream>

class md5 {
	HCRYPTPROV hCryptProv;
	HCRYPTHASH hHash;
public:
	const static int LENGTH = 32;
	md5() {
		hCryptProv = NULL;
		hHash = NULL;
	}
	bool initialize();
	bool finalize();
	bool add(char st[2]);
	bool add(int val);
	bool get(char buffer[LENGTH]);
};
