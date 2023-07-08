#include <conio.h>
#include "graphics/graph.h"
#include <chrono>
DestroyBlock destroyBlock;
BlockSurface blockSurface;
void graphMain(FlatCraft *game) {
	std::thread controllerThread(control);
	Graph graph(game);
	graph.display();
	
	
}

void control() {
	PlayerController* controller = & PlayerController::instance_;
	int ch;
	while (1) {
		if (GetAsyncKeyState('A') & 0x8000) {
			controller->left();
		}
		if (GetAsyncKeyState('S') & 0x8000) {
			controller->down();
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			controller->right();
		}
		if (GetAsyncKeyState('W') & 0x8000) {
			controller->up();
		}
	}
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
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&my_event) != 0) {
			if (my_event.type == SDL_QUIT) {
				quit = 1;
			}
			if (my_event.type == SDL_KEYDOWN) {
				if (my_event.key.keysym.sym == 'a')
					playerController->left();
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

}
void Graph::drawPlayer() {
	SDL_Texture* texture;
	Location playerLocation = FlatCraft::getInstance()->getPlayer()->getLocation();
	auto world = FlatCraft::getInstance()->getWorld("main_world");
	SDL_Rect rect;
	rect.x = windowWidth / 2;
	rect.y = 0.618*windowHeight;
	rect.w = rect.h = blockSize * 1.5;
	texture = SDL_CreateTextureFromSurface(renderer, blockSurface.getSurface(Material::BED_ROCK));
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Graph::drawMap() {
	SDL_Texture* texture;
	SDL_Rect rect;
	rect.x = windowWidth/2;
	rect.y = 14*blockSize;
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
	int ci, cj;
	ci = tempVec.getX();
	cj = tempVec.getY();
	SDL_Rect leftUpRect = rect;
	leftUpRect.x = rect.x - blockSize * ci;
	leftUpRect.y = rect.y - blockSize * (cj) ;
	int i, j;
	SDL_Rect tempRect = leftUpRect;
	for (i = 0; i < 42; i++) {
		tempRect.y = leftUpRect.y;
		for (j = 0; j < 26; j++) {
			material = materials_[i][25 - j][1];
			texture = backgroundTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			material = materials_[i][25 - j][0];
			texture = blockTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			tempRect.y += blockSize;
		}
		tempRect.x += blockSize;
	}
}

