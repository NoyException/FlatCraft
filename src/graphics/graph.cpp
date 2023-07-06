
#include "graphics/graph.h"
#include <chrono>
DestroyBlock destroyBlock;
BlockSurface blockSurface;
void graphMain(FlatCraft *game) {
	Graph graph(game);
	graph.display();
	
}
void Graph::display() {
	//World* world = game->getPlayer()->getLocation().getWorld();
	//World* world = FlatCraft::getInstance()->getWorld("test");
    //const char* path = "../../../../src/graphics/textures/birch.bmp";
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* pic = nullptr, *screen = nullptr;
	SDL_Window *window = SDL_CreateWindow("FlatCraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);//create window
	//pic = SDL_LoadBMP(path);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	while (true) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::milliseconds duration(50);
		std::chrono::system_clock::time_point targetTime = now + duration;
		std::this_thread::sleep_until(targetTime);//wait
		SDL_RenderClear(renderer); //clear before image in renderer
		draw(renderer);
		//SDL_RenderCopy(renderer, texture, NULL, &rect); 
		SDL_RenderPresent(renderer); //output image
	}
}
void Graph::draw(SDL_Renderer* renderer) {
	Location location("test", 64, 0);
	drawMap(location , renderer);

}

void Graph::drawMap(Location location, SDL_Renderer* renderer) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(Material::STONE));
	SDL_Rect rect;
	rect.x = 20;
	rect.y = 20;
	rect.w = rect.h = blockSize;
	SDL_RenderCopy(renderer, texture, NULL, &rect);


}