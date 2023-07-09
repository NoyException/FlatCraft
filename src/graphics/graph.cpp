﻿#include <conio.h>
#include "graphics/graph.h"
#include <chrono>


bool graphFinish = false;
DestroyBlock destroyBlock;
void graphMain() {
	graphFinish = false;
	Graph graph;
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	blockTexture = new BlockTexture(renderer);
	backgroundTexture = new BackgroundTexture(renderer);
	environmentTexture = new EnvironmentTexture(renderer);
	guiTexture = new GuiTexture(renderer);
	characterTexture = new CharacterTexture(renderer);
	PlayerController* playerController = &PlayerController::instance_;
	SDL_Event my_event;
	KeyState keyState;
	int mx, my;
	while (!graphFinish) {
		while (SDL_PollEvent(&my_event) != 0) {
			if (my_event.type == SDL_QUIT) {
				graphFinish = true;
			}
			else if (my_event.type == SDL_KEYDOWN || my_event.type == SDL_KEYUP) {
				if (my_event.type == SDL_KEYDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				switch (my_event.key.keysym.sym) {
					case SDLK_w: {
						playerController->setKeyState(Key::UP, keyState); 
						break;
					}
					case SDLK_s: {
						playerController->setKeyState(Key::DOWN, keyState);
						break;
					}
					case SDLK_a: {
						playerController->setKeyState(Key::LEFT, keyState);
						break;
					}
					case SDLK_d: {
						playerController->setKeyState(Key::RIGHT, keyState);
						break;
					}
					case SDLK_SPACE: {
						playerController->setKeyState(Key::SPACE, keyState);
						break;
					}
					case SDLK_LSHIFT:
					case SDLK_RSHIFT: {
						playerController->setKeyState(Key::SHIFT, keyState);
						break;
					}
					case SDLK_LCTRL:
					case SDLK_RCTRL: {
						playerController->setKeyState(Key::CTRL, keyState);
						break;
					}
								   
				}
			}
			else if (my_event.type == SDL_MOUSEBUTTONDOWN || my_event.type == SDL_MOUSEBUTTONUP) {
				if (my_event.type == SDL_MOUSEBUTTONDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				if (SDL_BUTTON_LEFT == my_event.button.button) {
					playerController->setKeyState(Key::LEFT_CLICK, keyState);
					//SDL_GetMouseState(&mx, &my);
					//std::cout << mx << " " << my << std::endl;
					
				}
				else if (SDL_BUTTON_RIGHT == my_event.button.button) {
					playerController->setKeyState(Key::RIGHT_CLICK, keyState);
				}
				
			}
		}
		 //clear before image in renderer
		SDL_RenderClear(renderer);
		draw();
		SDL_RenderPresent(renderer); //output image
	}
}

void Graph::drawHome() {
	SDL_Texture* texture;
	texture = guiTexture->getHome();
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 1280;
	rect.h = 768;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Graph::draw() {
	switch (gui) {
	case GUI::HOME:
//		drawHome();
//		break;
	case GUI::GAME:
		caculate();
		drawBackground();
		drawRain();
		drawMap();
		drawPlayer();
		drawGui();
		break;
	}
}

void Graph::drawGui() {
	SDL_Texture* texture;
	texture = guiTexture->getItemsBar();
	SDL_Rect rect;
	rect.x = 400;
	rect.y = 700;
	rect.h = 68;
	rect.w = 450;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void Graph::caculate() {
	{//get the information
		std::lock_guard<std::mutex> lock(WorldModel::instance_.mtx_);
		memcpy(materials_, WorldModel::instance_.materials_, sizeof(int) * 26 * 42 * 2);
		leftUpPosition_ = WorldModel::instance_.leftUpPosition_;
		cameraPosition_ = WorldModel::instance_.cameraPosition_;
		ticks = WorldModel::instance_.ticks_;
		ticks %= 24000;
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
	/*std::string tempString = TEXTURES_PATH;
	tempString.append("block/black10.png");
	SDL_Surface* pic = IMG_Load(tempString.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, pic);*/
	//SDL_FreeSurface(pic);

	SDL_Rect rect = leftUpRect;
	double wx = 0, wy = 0;
	rect.w = 1400;
	rect.h = 32;
	getWorldXY(rect.x, rect.y, wx, wy);
	double value;
	int r, g, b;
	double k =  1.0*abs(ticks - 12000) / 12000;
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255*k);
		SDL_RenderFillRect(renderer, &rect);
		rect.y += 32;
		wy--;
	}
	

}

void Graph::drawPlayer() {
	SDL_Texture* texture;
	SDL_Rect rect;
	int playerSize = 32;
	rect.x = windowWidth / 2  - 32*0.4;
	rect.y = 0.618*windowHeight - playerSize*0.8;
	rect.w = rect.h = playerSize * 0.8;

	//switch (PlayerModel::instance_.legAction_) {
	//case PlayerModel::LegAction::IDLE :
	//	texture = characterTexture->leg;
	//}

	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	//texture = characterTexture->body;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	//texture = characterTexture->sidehead;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	//texture = characterTexture->sidearm;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	texture = blockTexture->getTexture(Material::BED_ROCK);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	rect.x = 638;
	rect.x = 638;
	rect.y = 0;
	rect.w = 4;
	rect.h = 768;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	
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
	rainY += 2;
	if (rainY > 0)
		rainY = -200;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

