
#include "graphics/graph.h"
#include <chrono>
DestroyBlock destroyBlock;
void graphMain(FlatCraft *game) {
	//int rW = GetSystemMetrics(SM_CXSCREEN); // ∆¡ƒªøÌ∂» œÒÀÿ
	//int rH = GetSystemMetrics(SM_CYSCREEN); // ∆¡ƒª∏ﬂ∂» œÒÀÿ
	//initgraph(rW, rH);
//	initgraph(1280, 768);
	Graph graph(game);
	graph.display();
	
}
void Graph::display() {
	//World* world = game->getPlayer()->getLocation().getWorld();
	//World* world = FlatCraft::getInstance()->getWorld("test");
    const char* path = "../../../../src/graphics/textures/birch.bmp";

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 400;
	rect.w = 32;
	rect.h = 32;
	SDL_Surface* pic = nullptr, *screen = nullptr;
	SDL_Window *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 768, SDL_WINDOW_SHOWN);
	//pic = SDL_LoadBMP(path);
	pic = IMG_Load(path);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, pic);
	while (true) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::milliseconds duration(50);
		std::chrono::system_clock::time_point targetTime = now + duration;
		std::this_thread::sleep_until(targetTime);
		rect.x += 4;
		SDL_RenderClear(renderer); // «Â≥˝‰÷»æ∆˜
		SDL_RenderCopy(renderer, texture, NULL, &rect); // øΩ±¥Œ∆¿ÌµΩ‰÷»æ∆˜
		SDL_RenderPresent(renderer); // ‰÷»æ
	}
	//SDL_BlitSurface(pic, NULL, screen, NULL);
	//SDL_Rect rect;
	//rect.x = 100;
	//rect.y = 400;
	//rect.w = 10;
	//rect.h = 5;
	//SDL_BlitSurface(pic, NULL, screen, &rect);

	//SDL_UpdateWindowSurface(window);
}