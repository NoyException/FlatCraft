#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include "FlatCraft.h"
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
extern class DestroyBlock destroyBlock;
extern class BlockSurface blockSurface;
void graphMain(FlatCraft* game);

class BlockSurface {//store all of the texture
public:
	BlockSurface() {
		SDL_Surface* pic = nullptr;
		pic = IMG_Load("../../../../src/graphics/textures/block/stone.png");
		surfaces[Material::STONE] = pic;
		surfaces[Material::DIRT] = IMG_Load("../../../../src/graphics/textures/block/rooted_dirt.png");
		surfaces[Material::AIR] = IMG_Load("../../../../src/graphics/textures/block/white_stained_glass.png");
		//surfaces[Material::GRASS] = 
	}
	inline SDL_Surface* getSurface(Material material) {
		if (surfaces.find(material) == surfaces.end())
			return surfaces[Material::STONE];
		return surfaces[material];
	}
private:
	std::unordered_map<Material, SDL_Surface*> surfaces;
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
	Graph(FlatCraft* game) : game(game), windowWidth(1280), windowHeight(768), blockSize(32) {}
	void display();//display the graph, including world and player
	void drawMap(Location location, SDL_Renderer* renderer);//draw the map as location as the center
	void draw(SDL_Renderer* renderer);//draw the graph on the renderer
private:
	FlatCraft* game;
	int windowWidth, windowHeight;//pixel
	int blockSize;//pixel
};

#endif