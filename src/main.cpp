#include "common.h"
#include "FlatCraft.h"
#include <thread>
#include "graphics/graph.h"
#include "SDL.h"

#undef main
int main(){
    //SDL_main(0,{});
    FlatCraft game;
    std::cout << "Game starting" << std::endl;
    game.start();
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    std::thread graphThread(graphMain, &game);
    graphThread.detach();
    getchar();
    std::cout << "Game ended" << std::endl;
}

extern "C"
int SDL_main(int argc, char* argv[]) {
// 初始化SDL库
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init failed with error: " << SDL_GetError () << std::endl;
        return 1;
    }

    // 创建一个窗口
    SDL_Window* window = SDL_CreateWindow (
            "A Simple Window", // 标题
            SDL_WINDOWPOS_CENTERED, // 横坐标
            SDL_WINDOWPOS_CENTERED, // 纵坐标
            800, // 宽度
            600, // 高度
            SDL_WINDOW_SHOWN // 类型
    );
    if (window == NULL) {
        std::cout << "SDL_CreateWindow failed with error: " << SDL_GetError () << std::endl;
        return 1;
    }

    // 处理事件循环
    bool quit = false; // 是否退出程序的标志
    while (!quit) {
        SDL_Event event; // 用于存储事件的结构体
        while (SDL_PollEvent (&event) != 0) { // 不断地从事件队列中获取事件
            switch (event.type) { // 根据事件的类型来做相应的处理
                case SDL_QUIT: // 如果是关闭窗口的事件
                    quit = true; // 设置退出程序的标志为真
                    break;
                case SDL_KEYDOWN: // 如果是按下键盘的事件
                    if (event.key.keysym.sym == SDLK_ESCAPE) { // 如果按下的是ESC键
                        quit = true; // 设置退出程序的标志为真
                    }
                    break;
                default:
                    break;
            }
        }
        // 其他代码
    }

    // 销毁窗口
    SDL_DestroyWindow (window);

    // 退出SDL库
    SDL_Quit ();

//    std::ostream::sync_with_stdio(false);
    FlatCraft game;
    std::cout << "Game starting" << std::endl;
    game.start();
    //std::this_thread::sleep_for(std::chrono::seconds(10));
//    std::thread graphThread(graphMain, &game);
//    graphThread.detach();
    std::cout << "Game ended" << std::endl;
    return 0;
}

