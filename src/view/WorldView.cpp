#include "view/WorldView.h"



void WorldView::drawHome() {
	//SDL_Texture* texture;
	//texture = guiTexture->getHome();
	//SDL_Rect rect;
	//rect.x = rect.y = 0;
	//rect.w = 1280;
	//rect.h = 768;
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
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
	{
		std::shared_lock<std::shared_mutex> lock( binderMaterialMatrix_->getSharedMutex());
		tempVec = *binderCameraPosition_;
		leftUpPosition_ = *binderLeftUpPosition_;
		memcpy( materials_, binderMaterialMatrix_->getMatrix(), 42 * 28 * 2* sizeof(int));
	}
	
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
		value = (255 - (int)wy) / 255;
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

void WorldView::drawPlayer(int action) {
	SDL_Texture* texture;
	SDL_Rect rect;
	int playerSize = 64 * 3;
	rect.x = windowWidth / 2 - playerSize / 2;
	rect.y = 0.618 * windowHeight - playerSize * 0.8;
	rect.w = rect.h = playerSize * 0.8;
	rect.w = playerSize;
	static int lastAction = 0;
	static bool change = false;
	static long long lastTicks = 0;
	if (*binderTicks_ - lastTicks > 4) {
		change = !change;
		lastTicks = *binderTicks_;
	}
	if (lastAction < 2) {
		change = true;
	}
	lastAction = action;
	switch (action) {
	case 0:
		texture = characterTexture->right;
		break;
	case 1:
		texture = characterTexture->left;
		break;
	case 2:
		texture = characterTexture->rightAttack;
		break;
	case 3:
		texture = characterTexture->leftAttack;
		break;
	case 4:
		texture = characterTexture->rightRun;
		if (change)
			texture = characterTexture->right;
		break;
	case 5:
		texture = characterTexture->leftRun;
		if (change)
			texture = characterTexture->left;
		break;
	case 6:
		texture = characterTexture->rightRun;
		break;
	case 7:
		texture = characterTexture->leftRun;
		break;
	}
	//texture = characterTexture->right;
	//if(change)
	//	texture = characterTexture->rightRun;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
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
	static SDL_Rect srcRect = {0, 0, 16, 16};
	static long long waterTick = 0;
	if (*binderTicks_ - waterTick >= 2) {
		waterTick = *binderTicks_;
		srcRect.y += 16;
		if (srcRect.y >= 498)
			srcRect.y = 0;
	}
	for (i = 0; i < 42; i++) {
		tempRect.y = leftUpRect.y;
		for (j = 0; j < 28; j++) {
			material = materials_[i][j][0];
			texture = backgroundTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, material == Material::WATER? &srcRect: NULL, & tempRect);
			material = materials_[i][j][1];
			texture = blockTexture->getTexture(material);
			SDL_RenderCopy(renderer, texture, material == Material::WATER ? &srcRect : NULL, &tempRect);
			tempRect.y += blockSize;
		}
		tempRect.x += blockSize;
	}
}

void WorldView::drawRain(double v) {
	if ((*binderWeather_) == Weather::CLEAR) {
		if (weatherAlpha_ > 0)
			weatherAlpha_--;
		else
			return;
	}
	else if (weatherAlpha_ < 255)//rain
		weatherAlpha_++;
	SDL_Texture* texture = environmentTexture->getRain();
	SDL_SetTextureAlphaMod(texture, weatherAlpha_);
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

void WorldView::drawCrack(double process, SDL_Rect* rect) {
	if (process == 1)
		process = 0.99;
	int theProcess = (int)(process * 10);
	SDL_Texture* texture = blockTexture->getCrack(theProcess);
	SDL_RenderCopy(renderer, texture, NULL, rect);

}

void WorldView::drawDroppedItem(Material material, Vec2d position, int amount) {
	SDL_Rect rect = leftUpRect;
	rect.x += 32 * (position.getX() - leftUpPosition_.getX());
	rect.y -= 32 * (position.getY() - leftUpPosition_.getY());
	rect.w = rect.h = 16;
	rect.y -= rect.h;
	rect.x -= rect.w / 2;
	SDL_Texture* texture = blockTexture->getTexture(material);
	if(amount == 1)
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	else if (amount <= 32) {
		rect.x -= 2;
		rect.y -= 2;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		rect.x += 4;
		rect.y += 2;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
	else {
		rect.x -= 3;
		rect.y -= 3;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		rect.x += 6;
		rect.y += 1;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		rect.x -= 3;
		rect.y += 2;
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
}

void WorldView::setBinderCameraPosition(const std::function<void(RefPtr<Vec2d>)>& binder) {
	binder(binderCameraPosition_);
}


void WorldView::setBinderLeftUpPosition(const std::function<void(RefPtr<Vec2d>)>& binder) {
	binder(binderLeftUpPosition_);
}


void WorldView::setBinderTicks(const std::function<void(RefPtr<long long>)>& binder) {
	binder(binderTicks_);
}


void WorldView::setBinderMaterialMatrix(const std::function<void(RefPtr<MaterialMatrix>)>& binder) {
	binder(binderMaterialMatrix_);
}


void WorldView::setBinderWeather(const std::function<void(RefPtr<Weather>)>& binder) {
	binder(binderWeather_);
}

std::function<void()> WorldView::getNotificationWeatherChanged() {
	return [&]() {
		if (*binderWeather_ == Weather::CLEAR)
			weatherAlpha_ = 255;
		else
			weatherAlpha_ = 0;
	};
}

void WorldView::setCommandPause(const std::function<void(bool)>& command) {
	commandPause_ = command;
}