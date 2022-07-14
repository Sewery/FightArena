
#include "./Core/Game.h"

int main(int argc, char* argv[])
{
	
	try {
		Game game;
		game.run();
	}catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}