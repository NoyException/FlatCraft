#ifndef _MY_GRAPHICS_H_
#define _MY_GRAPHICS_H_
#include "view/PlayerView.h"
#include "view/WorldView.h"
extern bool graphFinish;
extern class DestroyBlock destroyBlock;
void control();

class DestroyBlock {
public:
	DestroyBlock() : flag(false), x(0), y(0), progress(0) {}
	inline void setFlag(bool flag) { this->flag = flag;  }
	inline void setXY(int x, int y) { this->x = x, this->y = y; }
	inline void setProgress(int progress) { this->progress = progress; }
	inline bool getFlag() { return flag; }
	inline int getX() const { return x; }
	inline int getY() const { return y; }
	inline int getProgress() const { return progress; }
private:
	bool flag;//true means a block is being destroied
	int x, y;//the world coordinate of the block
	int progress;//the progress of destroying the block, from 0 to 100
};

//TODO: 建立PlayerView.h/cpp


#endif