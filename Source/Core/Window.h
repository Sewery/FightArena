#pragma once
#include "../Player/Player.h"
#include "../Entities/ConstantBlock.h"

class Window {
	private:
		const std::string title;
		//The window we'll be rendering to
		SDL_Window* tWindow;
		//The window renderer
		SDL_Renderer* tRenderer ;
		//Main Music
		Mix_Music* tMusic ;
		//Player
		Player* player;
		//Globally used font
		std::vector<LightEntity*> tEntityBlocks;
		//
		TTF_Font* tFont;
		LightTexture* tFontTexture;
		//
		LightTexture* background;
		bool initWindow();
		void initObjects();
		bool loadFiles();
		
	public:
		//Window parameters
		static int currWindowWidth;
		static int currWindowHeight;
		static float ratioToBaseWidth;
		static float ratioToBaseHeight;

		Window(const std::string & name);
		void close();
		void update();
		[[nodiscard]] inline SDL_Renderer* getRenderer(){	return tRenderer;   }
		[[nodiscard]] inline SDL_Window* getWindow() { return tWindow; }
		void resizeFromBase(float ratioWidth, float ratioHeight);

};