#include <DxLib.h>
#include "SystemMain.h"

int android_main(void){
    SystemMain system;
    if (system.initialize()) {
        system.main();
    }
    system.finalize();
    return 0;
}
