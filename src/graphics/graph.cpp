#include <conio.h>
#include "graphics/graph.h"
#include <chrono>

DestroyBlock destroyBlock;
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
	blockTexture = new BlockTexture(renderer);
	backgroundTexture = new BackgroundTexture(renderer);
	environmentTexture = new EnvironmentTexture(renderer);
	PlayerController* playerController = FlatCraft::getInstance()->getPlayer()->getController();
	SDL_Event my_event;
	KeyState keyState;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&my_event) != 0) {
			if (my_event.type == SDL_QUIT) {
				quit = 1;
			}
			if (my_event.type == SDL_KEYDOWN || my_event.type == SDL_KEYUP) {
				if (my_event.type == SDL_KEYDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				switch (my_event.key.keysym.sym) {
					case 'w': {
						playerController->setKeyState(Key::UP, keyState); 
						break;
					}
					case 's': {
						playerController->setKeyState(Key::DOWN, keyState);
						break;
					}
					case 'a': {
						playerController->setKeyState(Key::LEFT, keyState);
						break;
					}
					case 'd': {
						playerController->setKeyState(Key::RIGHT, keyState);
						break;
					}
				}
			}
		}
		 //clear before image in renderer
		SDL_RenderClear(renderer);
		draw();
		SDL_RenderPresent(renderer); //output image
	}
}
	
void Graph::draw() {
	caculate();
	drawBackground();
	drawRain();
	drawMap();
	drawPlayer();
	
}
void Graph::caculate() {
	{//get the information
		std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);
		memcpy(materials_, WorldModel::instance_.materials_, sizeof(int) * 26 * 42 * 2);
		leftUpPosition_ = WorldModel::instance_.leftUpPosition_;
		cameraPosition_ = WorldModel::instance_.cameraPosition_;
	}
	SDL_Rect rect;
	rect.x = windowWidth / 2;
	rect.y = 0.618 * windowHeight;
	rect.w = rect.h = blockSize;
	Vec2d tempVec;
	tempVec = cameraPosition_;
	tempVec.subtract(leftUpPosition_);
	double ci, cj;
	ci = tempVec.getX();
	cj = tempVec.getY();
	leftUpRect = rect;
	leftUpRect.x = rect.x - blockSize * ci;
	leftUpRect.y = rect.y + blockSize * (cj);
}
void Graph::drawBackground() {
	SDL_Rect rect = leftUpRect;
	double wx = 0, wy = 0;
	rect.w = 1400;
	rect.h = 32;
	getWorldXY(rect.x, rect.y, wx, wy);
	int k = 0;
	double value;
	int r, g, b;
	while (rect.y < 770) {
		value = (255 - (int)wy) / 192;
		r = int(135 + value * 120);
		g = int(206 + value * 49);
		b = int(235 + value * 20);
		r = r > 255 ? 255 : r;
		g = g > 255 ? 255 : g;
		b = b > 255 ? 255 : b;
		if (wy < 64) {
			r = g = b = 0;
		}
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
		rect.y += 32;
		wy--;
	}
	

}

void Graph::drawPlayer() {
	SDL_Texture* texture;
	Location playerLocation = FlatCraft::getInstance()->getPlayer()->getLocation();
	auto world = FlatCraft::getInstance()->getWorld("main_world");
	SDL_Rect rect;
	rect.x = windowWidth / 2 - blockSize*0.75;
	rect.y = 0.618*windowHeight - blockSize*1.5;
	rect.w = rect.h = blockSize * 1.5;
	texture = blockTexture->getTexture(Material::BED_ROCK);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Graph::drawMap() {
	SDL_Texture* texture;
	int i, j;
	SDL_Rect tempRect = leftUpRect;
	Material material;
	for (i = 0; i < 42; i++) {
		tempRect.y = leftUpRect.y;
		for (j = 0; j < 26; j++) {
			material = materials_[i][j][1];
			texture = backgroundTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			material = materials_[i][j][0];
			texture = blockTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			tempRect.y += blockSize;
		}
		tempRect.x += blockSize;
	}
}

void Graph::drawRain() {
	SDL_Texture* texture = environmentTexture->getRain();
	SDL_Rect rect;
	static int rainY = -400;
	rect.x = 0;
	rect.y = rainY;
	rect.w = 1280;
	rect.h = 1000;
	rainY += 6;
	if (rainY > 0)
		rainY = -200;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

