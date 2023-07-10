
#include "app/Launcher.h"

#undef main
int main(){
    Launcher launcher;
    launcher.init();
    launcher.start();
    launcher.stop();
    launcher.end();
    return 0;
}