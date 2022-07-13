#include "Game.h"
#include "Window.h"
#include "../ResourceControllers/MouseKeyContr.h"

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr<<"SDL could not initialize! SDL Error: " << SDL_GetError() << '\n';
		return success = false;
	}
	if (TTF_Init() == -1)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: %" << TTF_GetError() << '\n';
		return success = false;
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cerr << "Warning: Linear texture filtering not enabled!";
		return success = false;
	}
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
		return success = false;
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError()<<'\n';
		return success = false;
	}
	gWindow = std::make_shared<Window>("Fighting ring");
	if (!gWindow)
	{
		return success = false;
	}
	return success;
}


//Frees media and shuts down SDL
void Game::close()
{
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void Game::run()
{
	//Start up SDL and create window
	if (!init())
	{
		std::cerr << "Failed to initialize!\n";
		return ;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	//While application is running
	Timer fpsTimer;
	Timer helper;
	fpsTimer.start();
	Uint64 frames = 0;
	while (!quit)
	{
		if (frames > (1 << 30))
		{
			frames = 0;
			fpsTimer.start();
		}
		helper.start();
		//Handle events on queue

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			

			switch (e.type)
			{
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_a:
						MouseKeyContr::keyboardState[SDLK_a] = true;
						break;
					case SDLK_d:
						MouseKeyContr::keyboardState[SDLK_d] = true;
						break;
					case SDLK_w:
						MouseKeyContr::keyboardState[SDLK_w] = true;
						break;
					case SDLK_s:
						MouseKeyContr::keyboardState[SDLK_s] = true;
						break;
					case SDLK_SPACE:
						MouseKeyContr::keyboardState[SDLK_SPACE] = true;
						break;
					default:
						break;
					}

					break;
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
					case SDLK_a:
						MouseKeyContr::keyboardState[SDLK_a] = false;
						break;
					case SDLK_d:
						MouseKeyContr::keyboardState[SDLK_d] = false;
						break;
					case SDLK_w:
						MouseKeyContr::keyboardState[SDLK_w] = false;
						break;
					case SDLK_s:
						MouseKeyContr::keyboardState[SDLK_s] = false;
						break;
					case SDLK_SPACE:
						MouseKeyContr::keyboardState[SDLK_SPACE] = false;
						break;
					default:
						break;
					}
				case SDL_WINDOWEVENT:
				{
					if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						int a=0, b=0;
						SDL_GetWindowSize(gWindow->getWindow(), &a, &b);
						Window::ratioToBaseHeight = (float)b / Game::SCREEN_HEIGHT;
						Window::ratioToBaseWidth = (float)a / Game::SCREEN_WIDTH;
					}
				}
					break;
			}
			
			if(e.type ==SDL_MOUSEBUTTONDOWN)
				MouseKeyContr::mouseClick = true;
			if (e.type == SDL_MOUSEBUTTONUP)
				MouseKeyContr::mouseClick = false;
			

		}
		frames++;
		float fps = frames / (fpsTimer.getTicks() / 1000.f);
		gWindow->update();

		int frameTicks = helper.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
		std::cout << " FPS:" << fps << '\n';
	}

	//Free resources and close SDL
	close();


}