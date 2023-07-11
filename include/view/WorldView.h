#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mouse.h"
#include "common.h"
const std::string TEXTURES_PATH = "../resources/textures/";
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
private:
	SDL_Texture* items_bar;
	SDL_Renderer* renderer;
	SDL_Texture* home;
	std::vector<SDL_Texture*> digits;
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
		tempString.append("block/dirt.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::DIRT] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/air.png");
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
		tempString.append("block/mywater.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::WATER] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		MYLOAD("block/oak_log.png", textures[Material::LOG]);
		MYLOAD("block/azalea_leaves.png", textures[Material::LEAVES]);
		cracks.resize(10);
		MYLOAD("block/destroy_stage_0.png", cracks[0]);
		MYLOAD("block/destroy_stage_1.png", cracks[1]);
		MYLOAD("block/destroy_stage_2.png", cracks[2]);
		MYLOAD("block/destroy_stage_3.png", cracks[3]);
		MYLOAD("block/destroy_stage_4.png", cracks[4]);
		MYLOAD("block/destroy_stage_5.png", cracks[5]);
		MYLOAD("block/destroy_stage_6.png", cracks[6]);
		MYLOAD("block/destroy_stage_7.png", cracks[7]);
		MYLOAD("block/destroy_stage_8.png", cracks[8]);
		MYLOAD("block/destroy_stage_9.png", cracks[9]);
	}
	inline SDL_Texture* getTexture(Material material) {
		if (textures.find(material) == textures.end())
			return textures[Material::BED_ROCK];
		return textures[material];
	}
	SDL_Texture* getCrack(int process) {
		return cracks[process];
	}
private:
	std::unordered_map<Material, SDL_Texture*> textures;
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> cracks;
};

class BackgroundTexture {//store the texutre of some background blocks to save time
public:
	BackgroundTexture(SDL_Renderer* renderer) : renderer(renderer) {
		std::string tempString = TEXTURES_PATH;
		tempString.append("behind/stone.png");
		SDL_Surface* pic = nullptr;
		pic = IMG_Load(tempString.c_str());
		textures[Material::STONE] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("behind/dirt.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::DIRT] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("behind/air.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::AIR] = nullptr;
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("behind/grass_block_side.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::GRASS] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("behind/bedrock.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::BED_ROCK] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		tempString = TEXTURES_PATH;
		tempString.append("block/mywater.png");
		pic = IMG_Load(tempString.c_str());
		textures[Material::WATER] = SDL_CreateTextureFromSurface(renderer, pic);
		SDL_FreeSurface(pic);
		MYLOAD("block/oak_log.png", textures[Material::LOG]);
		MYLOAD("block/azalea_leaves.png", textures[Material::LEAVES]);

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
		MYLOAD("steve/left.png", left);
		MYLOAD("steve/leftRun.png", leftRun);
		MYLOAD("steve/leftAttack.png", leftAttack);
		MYLOAD("steve/right.png", right);
		MYLOAD("steve/rightRun.png", rightRun);
		MYLOAD("steve/rightAttack.png", rightAttack);
	}
	SDL_Texture* body, * fronthead, * leftarm, * leg, * runlegs, * sidearm, * sidehead, * twoarms, * twolegs, * uprightarm, * upsidearm, * right, * left, * leftRun, * rightRun, * leftAttack, * rightAttack;
private:
	SDL_Renderer* renderer;
};

class WorldView {
public:
	WorldView() : windowWidth(1280), windowHeight(768), blockSize(32), renderer(nullptr), blockTexture(nullptr), backgroundTexture(nullptr), environmentTexture(nullptr), gui(GUI::HOME) {}
	void drawMap();//draw the map as location as the center
	void drawPlayer(int action);
	void drawRain(double v);
	void drawBackground();
	void drawItemBar();
	void drawHome();
	void drawCrack(double process, SDL_Rect* rect);

	void setBinderCameraPosition(const std::function<void(RefPtr<Vec2d>)>& binder);

	void setBinderLeftUpPosition(const std::function<void(RefPtr<Vec2d>)>& binder);

	void setBinderMaterialMatrix(const std::function<void(RefPtr<MaterialMatrix>)>& binder);

	void setBinderTicks(const std::function<void(RefPtr<long long>)>& binder);

	void setBinderWeather(const std::function<void(RefPtr<Weather>)>& binder);

	std::function<void()> getNotificationWeatherChanged();
	
	void setRenderer(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}

	void getWorldXY(int x, int y, double& wX, double& wY) {
		wX = binderCameraPosition_->getX() + (x - 640.0) / 32;
		wY = binderCameraPosition_->getY() - (y - 768 * 0.618) / 32;
	}
	void calculate();

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
	Material materials_[42][28][2];
	long long ticks;
	Weather weather_;
	GUI gui;
	Vec2d* binderCameraPosition_;
	Vec2d* binderLeftUpPosition_;
	long long* binderTicks_;
	MaterialMatrix* binderMaterialMatrix_;
	Weather* binderWeather_;

};





#endif // !WORLD_VIEW_H
