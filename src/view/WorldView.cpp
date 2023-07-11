#include "view/WorldView.h"

void WorldView::display() {
	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_Surface* pic = nullptr, * screen = nullptr;
	//SDL_Window* window = SDL_CreateWindow("FlatCraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);//create window
	//renderer = SDL_CreateRenderer(window, -1, 0);
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//blockTexture = new BlockTexture(renderer);
	//backgroundTexture = new BackgroundTexture(renderer);
	//environmentTexture = new EnvironmentTexture(renderer);
	//guiTexture = new GuiTexture(renderer);
	//characterTexture = new CharacterTexture(renderer);
	////	PlayerController* playerController = &PlayerController::instance_;
	//SDL_Event my_event;
	//KeyState keyState;
	//Vec2d clickPosition;
	//int mx, my;
	//while (!graphFinish) {
	//	calculate();
	//	while (SDL_PollEvent(&my_event) != 0) {
	//		SDL_GetMouseState(&mx, &my);
	//		clickPosition.setX(cameraPosition_.getX() + (mx - 640.0) / 32);
	//		clickPosition.setY(cameraPosition_.getY() - (my - 768 * 0.618) / 32);
	//		playerController->setClickPosition(clickPosition);
	//		/*std::cout << clickPosition.getX() << "  " << clickPosition.getY() << std::endl;*/
	//		if (my_event.type == SDL_QUIT) {
	//			graphFinish = true;
	//		}
	//		else if (my_event.type == SDL_KEYDOWN || my_event.type == SDL_KEYUP) {
	//			if (my_event.type == SDL_KEYDOWN)
	//				keyState = KeyState::DOWN;
	//			else
	//				keyState = KeyState::UP;
	//			switch (my_event.key.keysym.sym) {
	//			case SDLK_w: {
	//				playerController->setKeyState(Key::UP, keyState);
	//				break;
	//			}
	//			case SDLK_s: {
	//				playerController->setKeyState(Key::DOWN, keyState);
	//				break;
	//			}
	//			case SDLK_a: {
	//				playerController->setKeyState(Key::LEFT, keyState);
	//				break;
	//			}
	//			case SDLK_d: {
	//				playerController->setKeyState(Key::RIGHT, keyState);
	//				break;
	//			}
	//			case SDLK_SPACE: {
	//				playerController->setKeyState(Key::SPACE, keyState);
	//				break;
	//			}
	//			case SDLK_LSHIFT:
	//			case SDLK_RSHIFT: {
	//				playerController->setKeyState(Key::SHIFT, keyState);
	//				break;
	//			}
	//			case SDLK_LCTRL:
	//			case SDLK_RCTRL: {
	//				playerController->setKeyState(Key::CTRL, keyState);
	//				break;
	//			}

	//			}
	//		}
	//		else if (my_event.type == SDL_MOUSEBUTTONDOWN || my_event.type == SDL_MOUSEBUTTONUP) {
	//			if (my_event.type == SDL_MOUSEBUTTONDOWN)
	//				keyState = KeyState::DOWN;
	//			else
	//				keyState = KeyState::UP;
	//			if (SDL_BUTTON_LEFT == my_event.button.button) {
	//				playerController->setKeyState(Key::LEFT_CLICK, keyState);
	//				//SDL_GetMouseState(&mx, &my);
	//				//std::cout << mx << " " << my << std::endl;

	//			}
	//			else if (SDL_BUTTON_RIGHT == my_event.button.button) {
	//				playerController->setKeyState(Key::RIGHT_CLICK, keyState);
	//			}

	//		}
	//	}
	//	//clear before image in renderer
	//	SDL_RenderClear(renderer);
	//	draw();
	//	SDL_RenderPresent(renderer); //output image
	//}
}

void WorldView::drawHome() {
	SDL_Texture* texture;
	texture = guiTexture->getHome();
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = 1280;
	rect.h = 768;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void WorldView::draw() {
	//switch (gui) {
	//case GUI::HOME:
	//	//		drawHome();
	//	//		break;
	//case GUI::GAME:

	//	drawBackground();
	//	drawRain();
	//	drawMap();
	//	drawPlayer();
	//	drawItemBar();
	//	break;
	//}
}

void WorldView::drawItemBar() {
	//SDL_Texture* texture;
	//texture = guiTexture->getItemsBar();
	//SDL_Rect rect;
	//rect.x = 400;
	//rect.y = 700;
	//rect.h = 68;
	//rect.w = 440;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	//rect.x = 425;
	//rect.h = rect.w = 30;
	//rect.y += 20;
	//SDL_Rect digitRect = rect;
	//Material material;
	//digitRect.y += 18;
	//digitRect.w = 8;
	//digitRect.h = 12;
	//int num, digit;
	//for (int i = 0; i < 9; i++) {
	//	material = PlayerModel::instance_.actionBar_[i].material_;
	//	//material = Material::STONE;
	//	texture = blockTexture->getTexture(material);
	//	SDL_RenderCopy(renderer, texture, NULL, &rect);
	//	digitRect.x = rect.x;
	//	num = PlayerModel::instance_.actionBar_[i].amount_;
	//	//num = 63;
	//	digit = num / 10;
	//	if (digit) {
	//		texture = guiTexture->getDigit(digit);
	//		SDL_RenderCopy(renderer, texture, NULL, &digitRect);
	//		digitRect.x += 8;
	//		texture = guiTexture->getDigit(num % 10);
	//		SDL_RenderCopy(renderer, texture, NULL, &digitRect);
	//		digitRect.x += 8;
	//	}
	//	else if (num != 1) {
	//		texture = guiTexture->getDigit(num);
	//		SDL_RenderCopy(renderer, texture, NULL, &digitRect);
	//	}
	//	rect.x += 45;
	//}

}
void WorldView::calculate() {
	//    updateMaterials_(materials_, leftUpPosition_);
	//    leftUpPosition_ = getLeftUpPosition_();
	//    cameraPosition_ = getCameraPosition_();
	//    ticks = getTicks_();
	//    materialsUpdater_(materials_);//memcpy(materials_, WorldModel::instance_.materials_, sizeof(int) * 28 * 42 * 2);
	//    leftUpPosition_ = WorldModel::instance_.leftUpPosition_;
	//    cameraPosition_ = WorldModel::instance_.cameraPosition_;
	//    ticks = WorldModel::instance_.ticks_;
	
	//ticks %= 24000;

	SDL_Rect rect;
	rect.x = windowWidth / 2;
	rect.y = std::floor(0.618 * windowHeight);
	rect.w = rect.h = blockSize;
	Vec2d tempVec;
	tempVec = *binderCameraPosition_;
	leftUpPosition_ = *binderLeftUpPosition_;
	tempVec.subtract(leftUpPosition_);
	double ci, cj;
	ci = tempVec.getX();
	cj = tempVec.getY();
	leftUpRect = rect;
	leftUpRect.x = rect.x - blockSize * ci;
	leftUpRect.y = rect.y + blockSize * (cj);

}
void WorldView::drawBackground() {
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
	double k = 1.0 * abs(ticks - 12000) / 12000;
	k = 0.2;
	while (rect.y < 770) {
		value = (255 - (int)wy) / 192;
		r = int(135 + value * 120);
		g = int(206 + value * 49);
		b = int(235 + value * 20);
		r = r > 255 ? 255 : r;
		g = g > 255 ? 255 : g;
		b = b > 255 ? 255 : b;
		//if (wy < 64) {
		//	r = g = b = 0;
		//}
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 * k);
		SDL_RenderFillRect(renderer, &rect);
		rect.y += 32;
		wy--;
	}


}

void WorldView::drawPlayer() {
	//SDL_Texture* texture;
	//SDL_Rect rect;
	//int playerSize = 64 * 3;
	//rect.x = windowWidth / 2 - playerSize / 2;
	//rect.y = 0.618 * windowHeight - playerSize * 0.8;
	//rect.w = rect.h = playerSize * 0.8;
	//rect.w = playerSize;


	////texture = characterTexture->leg;
	////SDL_RenderCopy(renderer, texture, NULL, &rect);
	////texture = characterTexture->body;
	////SDL_RenderCopy(renderer, texture, NULL, &rect);
	////texture = characterTexture->sidehead;
	////SDL_RenderCopy(renderer, texture, NULL, &rect);
	////texture = characterTexture->sidearm;
	////SDL_RenderCopy(renderer, texture, NULL, &rect);
	//static bool change = false;
	//static long long lastTicks = ticks;
	//if (ticks - lastTicks > 7) {
	//	change = !change;
	//	lastTicks = ticks;
	//}
	//if (PlayerModel::instance_.direction_.getX() > 0) {
	//	if (PlayerModel::instance_.legAction_ == PlayerModel::LegAction::IDLE) {
	//		if (PlayerModel::instance_.handAction_ != PlayerModel::HandAction::IDLE && change)
	//			texture = characterTexture->rightAttack;
	//		else
	//			texture = characterTexture->right;
	//	}
	//	else
	//		texture = characterTexture->rightRun;
	//}
	//else {
	//	if (PlayerModel::instance_.legAction_ == PlayerModel::LegAction::IDLE) {
	//		if (PlayerModel::instance_.handAction_ != PlayerModel::HandAction::IDLE && change)
	//			texture = characterTexture->leftAttack;
	//		else
	//			texture = characterTexture->left;
	//	}
	//	else
	//		texture = characterTexture->leftRun;
	//}
	////texture = characterTexture->right;
	////if(change)
	////	texture = characterTexture->rightRun;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	//rect.x = 638;
	//rect.x = 638;
	//rect.y = 0;
	//rect.w = 4;
	//rect.h = 768;
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderFillRect(renderer, &rect);

}

void WorldView::drawMap() {
	SDL_Texture* texture;
	int i, j;
	SDL_Rect tempRect = leftUpRect;
	Material material;
	for (i = 0; i < 42; i++) {
		tempRect.y = leftUpRect.y;
		for (j = 0; j < 28; j++) {

			material = ( * binderMaterialMatrix_)[i][j][1];
			texture = backgroundTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			material = ( * binderMaterialMatrix_)[i][j][0];
			texture = blockTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, NULL, &tempRect);
			tempRect.y += blockSize;
		}
		tempRect.x += blockSize;
	}
}

void WorldView::drawRain(double v) {
	SDL_Texture* texture = environmentTexture->getRain();
	SDL_Rect rect;
	SDL_Rect rainRect;
	static int rainY = -400;
	static int rainX = 0;
	if (v > 0)
		rainX += 1;
	else if (v < 0)
		rainX -= 1;
	rect.x = 0;
	rect.y = rainY;
	rect.w = 1280;
	rect.h = 1000;
	rainRect.x = 320 + rainX;
	rainRect.y = 0;
	rainRect.w = 1280;
	rainRect.h = 768;
	rainY += 2;

	if (rainY > 0)
		rainY = -200;
	if (rainX > 300 || rainX < -300)
		rainX = 0;
	SDL_RenderCopy(renderer, texture, &rainRect, &rect);
}

void WorldView::setBinderCameraPosition(const std::function<void(RefPtr<Vec2d>)>& binder) {
	binder(binderCameraPosition_);
}


void WorldView::setBinderLeftUpPosition(const std::function<void(RefPtr<Vec2d>)>& binder) {
	binder(binderLeftUpPosition_);
}


void WorldView::setBinderTicks(const std::function<void(RefPtr<long long>)>& binder) {
	binder(binderTricks_);
}


void WorldView::setBinderMaterialMatrix(const std::function<void(RefPtr<MaterialMatrix>)>& binder) {
	binder(binderMaterialMatrix_);
}


void WorldView::setBinderWeather(const std::function<void(RefPtr<Weather>)>& binder) {
	binder(binderWeather_);
}

//TODO: 实现！
std::function<void()> WorldView::getNotificationWeatherChanged() {
	return [&]() {
		
		//这里的代码将在Model通知该View天气发生改变
	};
}