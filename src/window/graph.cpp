
#include "window/graph.h"

bool graphFinish;

void Window::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* pic = nullptr, * screen = nullptr;
	SDL_Window* window = SDL_CreateWindow("FlatCraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 768, SDL_WINDOW_SHOWN);//create window
	renderer_ = SDL_CreateRenderer(window, -1, 0);
	worldView_.setRenderer(renderer_);
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	worldView_.blockTexture = new BlockTexture(renderer_);
	worldView_.backgroundTexture = new BackgroundTexture(renderer_);
	worldView_.environmentTexture = new EnvironmentTexture(renderer_);
	worldView_.characterTexture = new CharacterTexture(renderer_);
	guiTexture_ = new GuiTexture(renderer_);
	KeyState keyState;
	SDL_Event my_event;
	Vec2d clickPosition;
	while (!graphFinish) {
		SDL_GetMouseState(&mx_, &my_);
		worldView_.calculate();
		while (SDL_PollEvent(&my_event) != 0) {
			clickPosition.setX(worldView_.binderCameraPosition_->getX() + (mx_ - 640.0) / 32);
			clickPosition.setY(worldView_.binderCameraPosition_->getY() - (my_ - 768 * 0.618) / 32);
			playerView_.commandChangeCursorPosition_(clickPosition);
			//std::cout << clickPosition.getX() << "  " << clickPosition.getY() << std::endl;
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
						playerView_.commandChangeKeyState_(Key::UP, keyState);
                        break;
                    }
                    case SDLK_s: {
						playerView_.commandChangeKeyState_(Key::DOWN, keyState);
                        break;
                    }
                    case SDLK_a: {
						playerView_.commandChangeKeyState_(Key::LEFT, keyState);
                        break;
                    }
                    case SDLK_d: {
						playerView_.commandChangeKeyState_(Key::RIGHT, keyState);
                        break;
                    }
                    case SDLK_SPACE: {
						playerView_.commandChangeKeyState_(Key::SPACE, keyState);
                        break;
                    }
                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT: {
						playerView_.commandChangeKeyState_(Key::SHIFT, keyState);
                        break;
                    }
                    case SDLK_LCTRL:
                    case SDLK_RCTRL: {
						playerView_.commandChangeKeyState_(Key::CTRL, keyState);
                        break;
                    }
					case SDLK_ESCAPE:
						playerView_.commandChangeKeyState_(Key::ESC, keyState);
						break;
					case SDLK_e:
						playerView_.commandChangeKeyState_(Key::OPENINVEMTORY, keyState);
						break;
				}
			}
			else if (my_event.type == SDL_MOUSEBUTTONDOWN || my_event.type == SDL_MOUSEBUTTONUP) {
				if (my_event.type == SDL_MOUSEBUTTONDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				if (SDL_BUTTON_LEFT == my_event.button.button) {
					playerView_.commandChangeKeyState_(Key::LEFT_CLICK, keyState);
					//SDL_GetMouseState(&mx, &my);
					//std::cout << mx << " " << my << std::endl;

				}
				else if (SDL_BUTTON_RIGHT == my_event.button.button) {
					playerView_.commandChangeKeyState_(Key::RIGHT_CLICK, keyState);
				}
			}
			else if (my_event.type == SDL_MOUSEWHEEL) {
				playerView_.commandScrollMouseWheel_(my_event.wheel.y);
			}
			my_event_ = my_event;
		}//end for event
		//clear before image in renderer
		draw();
	}
}

void Window::guiControl() {
	switch (gui_) {
	case GUI::GAME:
		if (my_event_.key.keysym.sym == SDLK_ESCAPE && my_event_.type == SDL_KEYUP) {
			gui_ = GUI::PAUSE;
			my_event_.key.keysym.sym = SDLK_l;
		}
		if (my_event_.key.keysym.sym == SDLK_e && my_event_.type == SDL_KEYUP) {
			gui_ = GUI::INVENTORY;
			my_event_.key.keysym.sym = SDLK_l;
		}
		break;
	case GUI::PAUSE:
			gui_ = GUI::ALREADYPAUSE;
			my_event_.key.keysym.sym = SDLK_l;
		break;
	case GUI::ALREADYPAUSE:
		pauseControl();
		break;
	case GUI::INVENTORY:
		gui_ = GUI::ALREADYINVENTORY;
		my_event_.key.keysym.sym = SDLK_l;
		break;
	case GUI::ALREADYINVENTORY:
		inventoryControl();
		break;
	}//end for switch
}

void Window::inventoryControl() {
	if (my_event_.key.keysym.sym == SDLK_e && my_event_.type == SDL_KEYUP) {
		gui_ = GUI::GAME;
		my_event_.key.keysym.sym = SDLK_l;
	}
	if (my_event_.type == SDL_MOUSEBUTTONUP && SDL_BUTTON_LEFT == my_event_.button.button) {
		if (inRegion(792, 250, 32)) {
			playerView_.commandClickedSlot_(0);
		}
		if (inRegion(664, 227, 32)) {
			playerView_.commandClickedSlot_(1);
		}
		if (inRegion(707, 227, 32)) {
			playerView_.commandClickedSlot_(2);
		}
		if (inRegion(664, 269, 32)) {
			playerView_.commandClickedSlot_(3);
		}
		if (inRegion(707, 269, 32)) {
			playerView_.commandClickedSlot_(3);
		}
		if (inRegion(460, 460 + 8 * 41 + 32, 378, 378 + 80 + 32)) {
			int k = (mx_ - 460) / 41 + 9 * ((my_ - 378) / 40) + 9;
			playerView_.commandClickedSlot_(k);
		}
	}
}

void Window::pauseControl() {
	if (my_event_.type == SDL_MOUSEBUTTONUP && SDL_BUTTON_LEFT == my_event_.button.button) {
		//outputMouse();
		if (mx_ > 375 && mx_ < 901) {
			if (my_ > 180 && my_ < 230) {
				gui_ = GUI::GAME;
				playerView_.commandChangeKeyState_(Key::ESC, KeyState::UP);
			}
			if (my_ > 345 && my_ < 391) {
				graphFinish = true;
			}
			
		}
	}
}

void Window::draw() {
	
	switch (gui_) {
	case GUI::GAME:
		SDL_RenderClear(renderer_);//clear
		drawGame();
		break;
	case GUI::PAUSE:
		SDL_RenderClear(renderer_);//clear
		drawPause();
		break;
	case GUI::ALREADYPAUSE:
		break;
	case GUI::INVENTORY:
	case GUI::ALREADYINVENTORY:
		drawInventory();
		break;
	}
	guiControl();
	SDL_RenderPresent(renderer_); //output image
}

void Window::drawInventory() {
	drawGame();
	int num;
	SDL_Texture* texture = guiTexture_->getInventory();
	SDL_Rect rect = { 1280/2 - 200, 768/2 - 200, 400, 400 };
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	MaterialStack* materialStacks = playerView_.binderMaterialStack_;
	rect.x = 792;
	rect.y = 250;
	rect.w = rect.h = 32;
	Material material;
	material = materialStacks[0].material_;
	//material = Material::BED_ROCK;
	num = materialStacks[0].amount_;
	texture = worldView_.blockTexture->getTexture(material);
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	drawDigit(num, &rect);
	material = materialStacks[1].material_;
	num = materialStacks[1].amount_;
	rect.x = 664;
	rect.y = 227;
	texture = worldView_.blockTexture->getTexture(material);
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	drawDigit(num, &rect);
	material = materialStacks[2].material_;
	num = materialStacks[2].amount_;
	rect.x = 707;
	texture = worldView_.blockTexture->getTexture(material);
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	drawDigit(num, &rect);
	material = materialStacks[3].material_;
	num = materialStacks[3].amount_;
	rect.x = 664;
	rect.y = 269;
	texture = worldView_.blockTexture->getTexture(material);
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	drawDigit(num, &rect);
	material = materialStacks[4].material_;
	num = materialStacks[4].amount_;
	rect.x = 707;
	texture = worldView_.blockTexture->getTexture(material);
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	drawDigit(num, &rect);
	rect.x = 460;
	rect.y = 378;
	for (int i = 9; i <= 44; i++) {
		//if (materialStacks + i == playerView_.binderMaterialStack_) {
		//	SDL_Rect tempRect = rect;
		//	tempRect.x -= 2;
		//	tempRect.y -= 2;
		//	tempRect.w += 4;
		//	tempRect.h += 4;
		//	SDL_SetRenderDrawColor(renderer_, 210, 255, 0, 255);
		//	SDL_RenderFillRect(renderer_, &tempRect);
		//}
		material = materialStacks[i].material_;
		num = materialStacks[i].amount_;
		material = Material::BED_ROCK;
		texture = worldView_.blockTexture->getTexture(material);
		SDL_RenderCopy(renderer_, texture, NULL, &rect);
		drawDigit(num, &rect);
		rect.x += 41;
		if (i == 17 || i == 26) {
			rect.x = 460;
			rect.y += 40;
		}
		if (i == 35) {
			rect.x = 460;
			rect.y += 52;
		}
	}
}

void Window::drawDroppedItems() {
	for (auto it = droppedItems_.begin(); it != droppedItems_.end(); ) {
		if ((*it)->itemState != ItemState::EXIST) {
			delete[](*it);
			it = droppedItems_.erase(it);
		}
		else {
			drawDroppedItem(*it);
			it++;
		}
	}
}

void Window::drawDroppedItem(DroppedItemView* droppedItemView) {
	worldView_.drawDroppedItem(droppedItemView->binderMaterialStack->material_, *droppedItemView->binderPosition_, droppedItemView->binderMaterialStack->amount_);
}

void Window::drawDigit(int num, SDL_Rect* rect) {
	int digit;
	SDL_Rect digitRect = *rect;
	digitRect.y += 18;
	digitRect.w = 8;
	digitRect.h = 12;
	SDL_Texture* texture;
	digit = num / 10;
	digitRect.x = rect->x + 20;
	if (num >= 10)
		digitRect.x -= 8;
	if (digit) {
		texture = guiTexture_->getDigit(digit);
		SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
		digitRect.x += 8;
		texture = guiTexture_->getDigit(num % 10);
		SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
		digitRect.x += 8;
	}
	else if (num != 1) {
		texture = guiTexture_->getDigit(num);
		SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
	}
}

void Window::drawItemsBar() {
	SDL_Texture* texture;
	texture = guiTexture_->getItemsBar();
	SDL_Rect rect;
	rect.x = 400;
	rect.y = 700;
	rect.h = 68;
	rect.w = 440;
	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	rect.x = 425;
	rect.h = rect.w = 30;
	rect.y += 20;
	SDL_Rect digitRect = rect;
	Material material;
	digitRect.y += 18;
	digitRect.w = 8;
	digitRect.h = 12;
	int num, digit;
	for (int i = 36; i <= 44; i++) {
		material = playerView_.binderMaterialStack_[i].material_;
		num = playerView_.binderMaterialStack_[i].amount_;
		if (i - 36 == *playerView_.binderSlot_ ) {
			SDL_Rect tempRect = rect;
			tempRect.x -= 2;
			tempRect.y -= 2;
			tempRect.w += 4;
			tempRect.h += 4;
			SDL_SetRenderDrawColor(renderer_, 210, 255, 0, 255);
			SDL_RenderFillRect(renderer_, &tempRect);
		}
		////material = Material::STONE;
		texture = worldView_.blockTexture->getTexture(material);
		SDL_RenderCopy(renderer_, texture, NULL, &rect);
		//num = 42;
		digit = num / 10;
		digitRect.x = rect.x + 20;
		if (num >= 10)
			digitRect.x -= 8;
		if (digit) {
			texture = guiTexture_->getDigit(digit);
			SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
			digitRect.x += 8;
			texture = guiTexture_->getDigit(num % 10);
			SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
			digitRect.x += 8;
		}
		else if (num != 1) {
			texture = guiTexture_->getDigit(num);
			SDL_RenderCopy(renderer_, texture, NULL, &digitRect);
		}
		rect.x += 45;
	}
}

void Window::drawGame() {
	worldView_.drawBackground();
	worldView_.drawRain(playerView_.binderVelocity_->getX());
	worldView_.drawMap();
	//draw crack if isDigging
	if (playerView_.isDigging) {
		if (*playerView_.binderBreakingProgress_ < 0.1)
			playerView_.isDigging = false;
		mouseBlockRect_.x = (worldView_.leftUpRect.x + (mx_- worldView_.leftUpRect.x)/32*32);
		mouseBlockRect_.y = (worldView_.leftUpRect.y + (my_- worldView_.leftUpRect.y)/32*32);
		mouseBlockRect_.w = mouseBlockRect_.h = 32;
		worldView_.drawCrack(*playerView_.binderBreakingProgress_, &mouseBlockRect_);
	}
	drawDroppedItems();
	drawPlayer();
	drawItemsBar();
}

void Window::drawPause() {
	drawGame();
	SDL_Rect rect = { 0, 0, 1280, 768 };
	SDL_RenderCopy(renderer_, guiTexture_->getPause(), NULL, &rect);
}

void Window::drawPlayer() {
	int action = 0;//idle
	if (*playerView_.binderBreakingProgress_ != 0)
		action = 2;//dig or attack
	if (playerView_.binderVelocity_->getX() != 0)
		action = 4;//run
	if (playerView_.binderVelocity_->getY() != 0)
		action = 6;//jump
	if (playerView_.binderDirection_->getX() < 0)
		action++;//left
	worldView_.drawPlayer(action);
}

DroppedItemView* Window::createDroppedItemView() {
	DroppedItemView* droppedItemView = new DroppedItemView();
	droppedItems_.push_back(droppedItemView);
	return droppedItemView;
}

WorldView &Window::getWorldView() {
    return worldView_;
}

PlayerView &Window::getPlayerView() {
    return playerView_;
}

