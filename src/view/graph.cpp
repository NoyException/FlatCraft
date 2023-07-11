
#include "view/graph.h"

bool graphFinish;

void Window::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* pic = nullptr, * screen = nullptr;
	SDL_Window* window = SDL_CreateWindow("FlatCraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 768, SDL_WINDOW_SHOWN);//create window
	renderer_ = SDL_CreateRenderer(window, -1, 0);
	worldView_.setRenderer(renderer_);
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	worldView_.blockTexture = new BlockTexture(renderer_);
	worldView_.backgroundTexture = new BackgroundTexture(renderer_);
	worldView_.environmentTexture = new EnvironmentTexture(renderer_);
	worldView_.guiTexture = new GuiTexture(renderer_);
	worldView_.characterTexture = new CharacterTexture(renderer_);

	SDL_Event my_event;
	KeyState keyState;
	Vec2d clickPosition;
	while (!graphFinish) {
		SDL_GetMouseState(&mx, &my);
		worldView_.calculate();
		while (SDL_PollEvent(&my_event) != 0) {
			clickPosition.setX(worldView_.binderCameraPosition_->getX() + (mx - 640.0) / 32);
			clickPosition.setY(worldView_.binderCameraPosition_->getY() - (my - 768 * 0.618) / 32);
			playerView_.commandChangeCursorPosition_(clickPosition);
			//std::cout << clickPosition.getX() << "  " << clickPosition.getY() << std::endl;
			if (my_event.type == SDL_QUIT) {
				graphFinish = true;
			}
			else if (my_event.type == SDL_KEYDOWN || my_event.type == SDL_KEYUP) {
				if (my_event.type == SDL_KEYDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				switch (my_event.key.keysym.sym) {
                    case SDLK_w: {
						playerView_.commandChangeKeyState_(Key::UP, keyState);
                        break;
                    }
                    case SDLK_s: {
						playerView_.commandChangeKeyState_(Key::DOWN, keyState);
                        break;
                    }
                    case SDLK_a: {
						playerView_.commandChangeKeyState_(Key::LEFT, keyState);
                        break;
                    }
                    case SDLK_d: {
						playerView_.commandChangeKeyState_(Key::RIGHT, keyState);
                        break;
                    }
                    case SDLK_SPACE: {
						playerView_.commandChangeKeyState_(Key::SPACE, keyState);
                        break;
                    }
                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT: {
						playerView_.commandChangeKeyState_(Key::SHIFT, keyState);
                        break;
                    }
                    case SDLK_LCTRL:
                    case SDLK_RCTRL: {
						playerView_.commandChangeKeyState_(Key::CTRL, keyState);
                        break;
                    }

				}
			}
			else if (my_event.type == SDL_MOUSEBUTTONDOWN || my_event.type == SDL_MOUSEBUTTONUP) {
				if (my_event.type == SDL_MOUSEBUTTONDOWN)
					keyState = KeyState::DOWN;
				else
					keyState = KeyState::UP;
				if (SDL_BUTTON_LEFT == my_event.button.button) {
					playerView_.commandChangeKeyState_(Key::LEFT_CLICK, keyState);
					//SDL_GetMouseState(&mx, &my);
					//std::cout << mx << " " << my << std::endl;

				}
				else if (SDL_BUTTON_RIGHT == my_event.button.button) {
					playerView_.commandChangeKeyState_(Key::RIGHT_CLICK, keyState);
				}
			}
			else if (my_event.type == SDL_MOUSEWHEEL) {
				playerView_.commandScrollMouseWheel_(my_event.wheel.y);
			}
		}
		//clear before image in renderer
		SDL_RenderClear(renderer_);
		draw();
		SDL_RenderPresent(renderer_); //output image
	}
}

void Window::draw() {
	//static long long a = 0;
	//a++;
	//std::cout << a << std::endl;
	worldView_.drawBackground();
	worldView_.drawRain(playerView_.binderVelocity_->getX());
	worldView_.drawMap();
	if (playerView_.isDigging) {
		if (*playerView_.binderBreakingProgress_ < 0.1)
			playerView_.isDigging = false;
		mouseBlockRect_.x = (worldView_.leftUpRect.x + (mx- worldView_.leftUpRect.x)/32*32);
		mouseBlockRect_.y = (worldView_.leftUpRect.y + (my- worldView_.leftUpRect.y)/32*32);
		mouseBlockRect_.w = mouseBlockRect_.h = 32;
		worldView_.drawCrack(*playerView_.binderBreakingProgress_, &mouseBlockRect_);
	}
	worldView_.drawPlayer(3);
	worldView_.drawItemBar();
}

WorldView &Window::getWorldView() {
    return worldView_;
}

PlayerView &Window::getPlayerView() {
    return playerView_;
}

