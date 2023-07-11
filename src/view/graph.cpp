
#include "view/graph.h"

bool graphFinish;

void Window::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* pic = nullptr, * screen = nullptr;
	SDL_Window* window = SDL_CreateWindow("FlatCraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 768, SDL_WINDOW_SHOWN);//create window
	renderer = SDL_CreateRenderer(window, -1, 0);
	worldView_.setRenderer(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	worldView_.blockTexture = new BlockTexture(renderer);
	worldView_.backgroundTexture = new BackgroundTexture(renderer);
	worldView_.environmentTexture = new EnvironmentTexture(renderer);
	worldView_.guiTexture = new GuiTexture(renderer);
	worldView_.characterTexture = new CharacterTexture(renderer);
	
	SDL_Event my_event;
	KeyState keyState;
	Vec2d clickPosition;
	int mx, my;
	while (!graphFinish) {
		while (SDL_PollEvent(&my_event) != 0) {
			SDL_GetMouseState(&mx, &my);
			//clickPosition.setX(cameraPosition_.getX() + (mx - 640.0) / 32);
			//clickPosition.setY(cameraPosition_.getY() - (my - 768 * 0.618) / 32);

			/*std::cout << clickPosition.getX() << "  " << clickPosition.getY() << std::endl;*/
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
					
					break;
				}
				case SDLK_s: {
					
					break;
				}
				case SDLK_a: {
					
					break;
				}
				case SDLK_d: {
					
					break;
				}
				case SDLK_SPACE: {
					
					break;
				}
				case SDLK_LSHIFT:
				case SDLK_RSHIFT: {
					
					break;
				}
				case SDLK_LCTRL:
				case SDLK_RCTRL: {
					
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
					
					//SDL_GetMouseState(&mx, &my);
					//std::cout << mx << " " << my << std::endl;

				}
				else if (SDL_BUTTON_RIGHT == my_event.button.button) {
					
				}

			}
		}
		//clear before image in renderer
		SDL_RenderClear(renderer);
		draw();
		SDL_RenderPresent(renderer); //output image
	}
}

void Window::draw() {
	worldView_.calculate();
	worldView_.drawBackground();
	worldView_.drawRain(playerView_.binderVelocity_->getX());
	worldView_.drawMap();
	//worldView_.drawPlayer();
	//worldView_.drawItemBar();
}

