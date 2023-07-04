#include "common.h"
#include "FlatCraft.h"

int main() {
//    std::ostream::sync_with_stdio(false);
    FlatCraft game;
    std::cout << "Game starting" << std::endl;
    game.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Game ended" << std::endl;
    return 0;
}

