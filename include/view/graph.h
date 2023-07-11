#ifndef _MY_GRAPHICS_H_
#define _MY_GRAPHICS_H_
#include "view/PlayerView.h"
#include "view/WorldView.h"
extern bool graphFinish;

class Window {
public:
	void start();
	void draw();

    WorldView &getWorldView();

    PlayerView &getPlayerView();

	void drawPlayer();

private:
	int mx, my;
	SDL_Renderer* renderer_ = nullptr;
	WorldView worldView_;
	PlayerView playerView_;
	SDL_Rect mouseBlockRect_;

};


#endif