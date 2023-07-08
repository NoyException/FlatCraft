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
				std::cout << (keyState == KeyState::DOWN) ? "down" : "up";
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
void Graph::draw() {
	drawMap();
	drawPlayer();
	drawRain();
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
	SDL_Rect rect;
	rect.x = windowWidth/2;
	rect.y = 0.618*windowHeight;
	rect.w = rect.h = blockSize;
	Vec2d leftUpPosition_;
	Vec2d cameraPosition_;
	Vec2d tempVec;
	Material materials_[42][26][2];
	{
		std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);
		memcpy(materials_, WorldModel::instance_.materials_, sizeof(int)*26*42*2);
		leftUpPosition_ = WorldModel::instance_.leftUpPosition_;
		cameraPosition_ = WorldModel::instance_.cameraPosition_;
	}
	tempVec = cameraPosition_;
	tempVec.subtract(leftUpPosition_);
	Material material;
	double ci, cj;
	ci = tempVec.getX();
	cj = tempVec.getY();
	SDL_Rect leftUpRect = rect;
	leftUpRect.x = rect.x - blockSize * ci;
	leftUpRect.y = rect.y + blockSize * (cj) ;
	int i, j;
	SDL_Rect tempRect = leftUpRect;
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

}

