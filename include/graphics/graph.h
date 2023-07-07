#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include "FlatCraft.h"
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include <Windows.h>
#include "WorldModel.h"
extern class DestroyBlock destroyBlock;
extern class BlockSurface blockSurface;
void graphMain(FlatCraft* game);

//may be abondoned
class BlockSurface {//store all of the texture
public:
	BlockSurface() {
		SDL_Surface* pic = nullptr;
		pic = IMG_Load("../../../../src/graphics/textures/block/stone.png");
		surfaces[Material::STONE] = pic;
		surfaces[Material::DIRT] = IMG_Load("../../../../src/graphics/textures/block/rooted_dirt.png");
		surfaces[Material::AIR] = IMG_Load("../../../../src/graphics/textures/block/white_stained_glass.png");
		surfaces[Material::GRASS] = IMG_Load("../../../../src/graphics/textures/block/azalea_top.png");
		surfaces[Material::BED_ROCK] = IMG_Load("../../../../src/graphics/textures/block/bedrock.png");
		surfaces[Material::WATER] = IMG_Load("../../../../src/graphics/textures/painting/water.png");
	}
	~BlockSurface() {
		for (auto it : surfaces) {
			SDL_FreeSurface(it.second);
		}
	}
	inline SDL_Surface* getSurface(Material material) {
		if (surfaces.find(material) == surfaces.end())
			return surfaces[Material::STONE];
		return surfaces[material];
	}
private:
	std::unordered_map<Material, SDL_Surface*> surfaces;
};

class BlockTexture {//store the texutre of some blocks to save time
public:
	BlockTexture(SDL_Renderer* renderer) : renderer(renderer) {
		SDL_Surface* pic = nullptr;
		pic = IMG_Load("../../../../src/graphics/textures/block/stone.png");
		textures[Material::STONE] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		pic = IMG_Load("../../../../src/graphics/textures/block/rooted_dirt.png");
		textures[Material::DIRT] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		pic = IMG_Load("../../../../src/graphics/textures/block/white_stained_glass.png");
		textures[Material::AIR] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		pic = IMG_Load("../../../../src/graphics/textures/block/azalea_top.png");
		textures[Material::GRASS] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		pic = IMG_Load("../../../../src/graphics/textures/block/bedrock.png");
		textures[Material::BED_ROCK] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		pic = IMG_Load("../../../../src/graphics/textures/painting/water.png");
		textures[Material::WATER] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
	}
	inline SDL_Texture* getTexture(Material material) {
		if (textures.find(material) == textures.end())
			return textures[Material::STONE];
		return textures[material];
	}
private:
	std::unordered_map<Material, SDL_Texture*> textures;
	SDL_Renderer* renderer;
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
	Graph(FlatCraft* game) : game(game), windowWidth(1280), windowHeight(768), blockSize(32), renderer(nullptr), blockTexture(nullptr) {}
	void display();//display the graph, including world and player
	void drawMap();//draw the map as location as the center
	void draw();//draw the graph on the renderer
	void drawPlayer();
private:
	FlatCraft* game;
	int windowWidth, windowHeight;//pixel
	int blockSize;//pixel
	SDL_Renderer* renderer;
	BlockTexture* blockTexture;
};

#endif