#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include "FlatCraft.h"
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include <Windows.h>
#include "WorldModel.h"
const std::string TEXTURES_PATH = "../resources/textures/";
extern class DestroyBlock destroyBlock;
void graphMain(FlatCraft* game);
void control();

class RainTexture {

};

class BlockTexture {//store the texutre of some blocks to save time
public:
	BlockTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("block/stone.png");
		SDL_Surface* pic = nullptr;
		pic = IMG_Load(tempString.c_str());
		textures[Material::STONE] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/rooted_dirt.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::DIRT] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/white_stained_glass.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::AIR] = SDL_CreateTextureFromSurface(renderer, pic);  
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/azalea_top.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::GRASS] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/bedrock.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::BED_ROCK] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("painting/water.png");
		pic = IMG_Load(tempString.c_str());
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

class BackgroundTexture {//store the texutre of some background blocks to save time
public:
	BackgroundTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("block/cracked_stone_bricks.png");
		SDL_Surface* pic = nullptr;
		pic = IMG_Load(tempString.c_str());
		textures[Material::STONE] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/coarse_dirt.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::DIRT] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/white_stained_glass.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::AIR] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/grass_block_side.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::GRASS] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/bedrock.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::BED_ROCK] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("painting/blue_wool.png");
		pic = IMG_Load(tempString.c_str());
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
	Graph(FlatCraft* game) : game(game), windowWidth(1280), windowHeight(768), blockSize(32), renderer(nullptr), blockTexture(nullptr), backgroundTexture(nullptr) {}
	void display();//display the graph, including world and player
	void drawMap();//draw the map as location as the center
	void draw();//draw the graph on the renderer
	void drawPlayer();
	void drawRain();
private:
	FlatCraft* game;
	int windowWidth, windowHeight;//pixel
	int blockSize;//pixel
	SDL_Renderer* renderer;
	BlockTexture* blockTexture;
	BackgroundTexture* backgroundTexture;
};

#endif