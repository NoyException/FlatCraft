#ifndef _MY_GRAPHICS_H_
#define _MY_GRAPHICS_H_
#include "view/PlayerView.h"
#include "view/WorldView.h"
extern bool graphFinish;
extern class DestroyBlock destroyBlock;
void control();

class DestroyBlock {
public:
	DestroyBlock() : flag_(false), x_(0), y_(0), progress_(0) {}
	inline void setFlag(bool flag) { this->flag_ = flag;  }
	inline void setXY(int x, int y) { this->x_ = x, this->y_ = y; }
	inline void setProgress(int progress) { this->progress_ = progress; }
	inline bool getFlag() { return flag_; }
	inline int getX() const { return x_; }
	inline int getY() const { return y_; }
	inline int getProgress() const { return progress_; }
private:
	bool flag_;//true means a block is being destroied
	int x_, y_;//the world coordinate of the block
	int progress_;//the progress of destroying the block, from 0 to 100
};

class Window {
public:
	void start();
	void draw();

    WorldView &getWorldView();

    PlayerView &getPlayerView();

private:
	int mx, my;
	SDL_Renderer* renderer_ = nullptr;
	WorldView worldView_;
	PlayerView playerView_;
	SDL_Rect mouseBlockRect_;

};


#endif