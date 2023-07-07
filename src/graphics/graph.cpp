
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
	renderer = SDL_CreateRenderer(window, -1, 0);
	PlayerController* playerController = FlatCraft::getInstance()->getPlayer()->getController();
	SDL_Event my_event;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&my_event) != 0) {
			if (my_event.type == SDL_QUIT) {
				quit = 1;
			}
			if (my_event.type == SDL_KEYDOWN) {
				//switch (my_event.key.keysym.sym) {
				//case 'w':
				//{
				//	Location location = FlatCraft::getInstance()->getPlayer()->getLocation();
				//	location.setY(location.getY() + 0.2);
				//	FlatCraft::getInstance()->getPlayer()->teleport(location);
				//	//std::cout << "h";
				//	//playerController->up();
				//	break;
				//}
				//case 's':
				//{
				//	Location location = FlatCraft::getInstance()->getPlayer()->getLocation();
				//	location.setY(location.getY() - 0.2);
				//	FlatCraft::getInstance()->getPlayer()->teleport(location);
				//	break;
				//}
				//case 'd':
				//{
				//	Location location = FlatCraft::getInstance()->getPlayer()->getLocation();
				//	location.setX(location.getX() + 0.2);
				//	FlatCraft::getInstance()->getPlayer()->teleport(location);
				//	//playerController->left();
				//	break;
				//}
				//case 'a':
				//{
				//	Location location = FlatCraft::getInstance()->getPlayer()->getLocation();
				//	location.setX(location.getX() - 0.2);
				//	FlatCraft::getInstance()->getPlayer()->teleport(location);
				//	break;
				//}
				}
			}
		}
		SDL_RenderClear(renderer); //clear before image in renderer
		draw();
		SDL_RenderPresent(renderer); //output image
		
	}
	
	//while (true) {
	//	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	//	std::chrono::milliseconds duration(50);
	//	std::chrono::system_clock::time_point targetTime = now + duration;
	//	std::this_thread::sleep_until(targetTime);//wait
	//	
	//	
	//	SDL_RenderClear(renderer); //clear before image in renderer
	//	draw();
	//	//SDL_RenderCopy(renderer, texture, NULL, &rect); 
	//	SDL_RenderPresent(renderer); //output image
	//}
}
void Graph::draw() {
	drawMap();
	drawPlayer();

}
void Graph::drawPlayer() {
	SDL_Texture* texture;
	Location playerLocation = FlatCraft::getInstance()->getPlayer()->getLocation();
	auto world = FlatCraft::getInstance()->getWorld("main_world");
	SDL_Rect rect;
	rect.x = windowWidth / 2;
	rect.y = windowHeight * 3 / 4;
	rect.w = rect.h = blockSize * 1.5;
	//rect.x += (playerLocation.getX() - (int) playerLocation.getX()) * blockSize;
	//rect.y += (playerLocation.getY() - playerLocation.getBlockY()) * blockSize;
	texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(Material::BED_ROCK));
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Graph::drawMap() {
	SDL_Texture* texture;
	SDL_Rect rect;
	rect.x = windowWidth/2;
	rect.y = windowHeight*3/4;
	rect.w = rect.h = blockSize;
	Location playerLocation = FlatCraft::getInstance()->getPlayer()->getLocation();
	auto world = FlatCraft::getInstance()->getWorld("main_world");
	Material material;
	rect.x += (playerLocation.getX() - playerLocation.getBlockX())*blockSize;
	rect.y += (playerLocation.getY() - playerLocation.getBlockY())*blockSize;
	int i, j;
	int px, py;
	px = playerLocation.getBlockX();
	py = playerLocation.getBlockY();
	SDL_Rect tempRect;
	for (i = 0; rect.x + i * blockSize < windowWidth; i++) {
		if (px + i >= 128 || px + i < -127)
			break;
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = 0; rect.y + j * blockSize < windowHeight; j++, tempRect.y += blockSize) {
			if (py - j > 255 || py - j < 0)
				break;
			material = world->getBlock(px + i, py - j, true)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
			//SDL_RenderPresent(renderer);
		}
		tempRect = rect;
		tempRect.x += i * blockSize;
		tempRect.y -= blockSize;
		for (j = -1; rect.y + j * blockSize > -blockSize*2; j--, tempRect.y -= blockSize) {
			if (py - j > 255 || py - j < 0)
				break;
			material = world->getBlock(px + i, py - j, true)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
			//SDL_RenderPresent(renderer);
		}
	}
	for (i = -1; rect.x + i * blockSize > -blockSize; i--) {
		if (px + i >= 128 || px + i < -127)
			break;
		tempRect = rect;
		tempRect.x += i * blockSize;
		for (j = 0; rect.y + j * blockSize < windowHeight; j++, tempRect.y += blockSize) {
			if (py - j > 255 || py - j < 0)
				break;
			material = world->getBlock(px + i, py - j, true)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
			//			SDL_RenderPresent(renderer);

		}
		tempRect = rect;
		tempRect.x += i * blockSize;
		tempRect.y -= blockSize;
		for (j = -1; rect.y + j * blockSize > -blockSize * 2; j--, tempRect.y -= blockSize) {
			if (py - j > 255 || py - j < 0)
				break;
			material = world->getBlock(px + i, py - j, true)->getMaterial();
			texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(material));
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			SDL_DestroyTexture(texture);
			//			SDL_RenderPresent(renderer);
		}
	}
	

}