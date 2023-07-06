﻿
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
	SDL_Texture* texture;
	SDL_Rect rect;
	rect.x = windowWidth/2;
	rect.y = windowHeight*3/4;
	rect.w = rect.h = blockSize;
	Location playerLocation = FlatCraft::getInstance()->getPlayer()->getLocation();
	auto world = FlatCraft::getInstance()->getWorld("main_world");
	Material material =  world->getBlock(playerLocation)->getMaterial();
	texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
	rect.x += (playerLocation.getX() - playerLocation.getBlockX())*blockSize;
	rect.y += (playerLocation.getY() - playerLocation.getBlockY())*blockSize;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	int i, j;
	int px, py;
	px = playerLocation.getBlockX();
	py = playerLocation.getBlockY();
	SDL_Rect tempRect;
	for (i = 0; rect.x + i * blockSize < windowWidth; i++) {
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = 0; rect.y + j * blockSize < windowHeight; j++, tempRect.y += blockSize) {
			material = world->getBlock(px + i, py - j)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
		}
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = -1; rect.y + j * blockSize > -blockSize; j--, tempRect.y -= blockSize) {
			material = world->getBlock(px + i, py - j)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
		}
	}
	for (i = -1; rect.x + i * blockSize > -blockSize; i--) {
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = 0; rect.y + j * blockSize < windowHeight; j++, tempRect.y += blockSize) {
			material = world->getBlock(px + i, py - j)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
		}
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = -1; rect.y + j * blockSize > -blockSize; j--, tempRect.y -= blockSize) {
			material = world->getBlock(px + i, py - j)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
		}
	}
	

}