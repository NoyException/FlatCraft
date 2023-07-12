#ifndef _MY_GRAPHICS_H_
#define _MY_GRAPHICS_H_
#include "view/PlayerView.h"
#include "view/WorldView.h"
#include "view/DroppedItemView.h"
#include "view/EnitityView.h"
extern bool graphFinish;

enum class GUI : int {
	HOME,
	GAME,
	PAUSE,
	ALREADYPAUSE
};

class GuiTexture {
public:
	GuiTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("gui/items_bar.png");
		SDL_Surface* pic = IMG_Load(tempString.c_str());
		items_bar = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("gui/home.png");
		pic = IMG_Load(tempString.c_str());
		home = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		//load digit
		digits.resize(10);
		MYLOAD("digit/0.png", digits[0]);
		MYLOAD("digit/1.png", digits[1]);
		MYLOAD("digit/2.png", digits[2]);
		MYLOAD("digit/3.png", digits[3]);
		MYLOAD("digit/4.png", digits[4]);
		MYLOAD("digit/5.png", digits[5]);
		MYLOAD("digit/6.png", digits[6]);
		MYLOAD("digit/7.png", digits[7]);
		MYLOAD("digit/8.png", digits[8]);
		MYLOAD("digit/9.png", digits[9]);

		MYLOAD("gui/pause.png", pause);
	}
	inline SDL_Texture* getItemsBar() {
		return items_bar;
	}
	inline SDL_Texture* getHome() {
		return home;
	}
	inline SDL_Texture* getDigit(int digit) {
		return digits[digit];
	}
	inline SDL_Texture* getPause() {
		return pause;
	}
private:
	SDL_Texture* items_bar;
	SDL_Renderer* renderer;
	SDL_Texture* home;
	std::vector<SDL_Texture*> digits;
	SDL_Texture* pause;
};

class Window {
public:
	Window() : gui_(GUI::GAME) {}
	void start();
	void draw();

	DroppedItemView* createDroppedItemView();

    WorldView &getWorldView();

    PlayerView &getPlayerView();

	void drawPlayer();

	void drawPause();

	void drawGame();

	void guiControl();

private:
	int mx_, my_;
	SDL_Event my_event_;
	SDL_Renderer* renderer_ = nullptr;
	WorldView worldView_;
	PlayerView playerView_;
	SDL_Rect mouseBlockRect_;
	GUI gui_;
	GuiTexture* guiTexture_;
	std::list<DroppedItemView*> droppedItems_;

};


#endif