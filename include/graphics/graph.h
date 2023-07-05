#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <graphics.h>
#include "FlatCraft.h"
#include <unordered_map>
extern class DestroyBlock destroyBlock;
void graphMain(FlatCraft* game);

class BlockGraph {//search the image through material
public:
	BlockGraph();
	inline IMAGE* getImage(Material material) { }
private:
	std::vector<IMAGE> imgs;
};

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

class Graph {
public:
	Graph(FlatCraft* game) : game(game) {}
	void display();//display the graph, including world and player
	void drawMap(Location location);//draw the map as location as the center
private:
	FlatCraft* game;
};

#endif