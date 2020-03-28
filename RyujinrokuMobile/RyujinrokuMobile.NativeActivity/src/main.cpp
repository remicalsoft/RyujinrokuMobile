#include <DxLib.h>
#include "UpdateChecker.h"
#include "SystemMain.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	if (!UpdateChecker::isUpdate()) {
		return 0;
	}
	SystemMain *system;
	system = new SystemMain();
	system->main();
	delete system;
	return 0;
}