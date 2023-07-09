#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include <Windows.h>
#include "WorldModel.h"
#include "SDL_mouse.h"
#include "PlayerController.h"
#include <iostream>
#include "PlayerModel.h"
const std::string TEXTURES_PATH = "../resources/textures/";
extern bool graphFinish;
extern class DestroyBlock destroyBlock;
void graphMain();
void control();

#define MYLOAD(path, name) \
do{	\
tempString = TEXTURES_PATH;\
tempString.append(path);\
pic = IMG_Load(tempString.c_str());\
name = SDL_CreateTextureFromSurface(renderer, pic);\
SDL_FreeSurface(pic);\
}while(0);

enum class GUI : int {
	HOME,
	GAME
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
	}
	inline SDL_Texture* getItemsBar() {
		return items_bar;
	}
	inline SDL_Texture* getHome() {
		return home;
	}
private:
	SDL_Texture* items_bar;
	SDL_Renderer* renderer;
	SDL_Texture* home;
};

class EnvironmentTexture {
public:
	EnvironmentTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("environment/myRain.png");
		SDL_Surface* pic = IMG_Load(tempString.c_str());
		rainTexture = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
	}
	inline SDL_Texture* getRain() {
		return rainTexture;
	}
private:
	SDL_Texture* rainTexture;
	SDL_Renderer* renderer;
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
		tempString.append("block/air.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::AIR] = nullptr;
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
		textures[Material::AIR] = nullptr;
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

class CharacterTexture {
public:
	CharacterTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("character/body.png");
		SDL_Surface* pic = IMG_Load(tempString.c_str());
		body = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("character/fronthead.png");
		pic = IMG_Load(tempString.c_str());
		fronthead = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("character/leftarm.png");
		pic = IMG_Load(tempString.c_str());
		leftarm = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		MYLOAD("character/leg.png", leg);
		MYLOAD("character/runlegs.png", runlegs);
		MYLOAD("character/sidearm.png", sidearm);
		MYLOAD("character/sidehead.png", sidehead);
		MYLOAD("character/twoarms.png", twoarms);
		MYLOAD("character/twolegs.png", twolegs);
		MYLOAD("character/uprightarm.png", uprightarm);
		MYLOAD("character/upsidearm.png", upsidearm);
	}
	SDL_Texture* body, *fronthead, *leftarm, *leg, *runlegs, *sidearm, *sidehead, *twoarms, *twolegs, *uprightarm, *upsidearm;
private:
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
	Graph() : windowWidth(1280), windowHeight(768), blockSize(32), renderer(nullptr), blockTexture(nullptr), backgroundTexture(nullptr), environmentTexture(nullptr), gui(GUI::HOME) {}
	void display();//display the graph, including world and player
	void drawMap();//draw the map as location as the center
	void draw();//draw the graph on the renderer
	void drawPlayer();
	void drawRain();
	void drawBackground();
	void drawGui();
	void drawHome();
private:
	inline void getWorldXY(int x, int y, double& wX, double &wY) {
		wX = cameraPosition_.getX() + (x - 640) / 32;
		wY = cameraPosition_.getY() - (y - 768 * 0.618) / 32;
	}
	inline void caculate();

	int windowWidth, windowHeight;//pixel
	int blockSize;//pixel
	SDL_Renderer* renderer;
	BlockTexture* blockTexture;
	BackgroundTexture* backgroundTexture;
	EnvironmentTexture* environmentTexture;
	GuiTexture* guiTexture;
	CharacterTexture* characterTexture;
	Vec2d leftUpPosition_;
	Vec2d cameraPosition_;
	SDL_Rect leftUpRect;
	Material materials_[42][26][2];
	long long ticks;
	GUI gui;
};

#endif