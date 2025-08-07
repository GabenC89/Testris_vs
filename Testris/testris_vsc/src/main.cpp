//Extra Lib Includes
#include <iostream>
#include <string>

//Internal Dependencies
#include "GameEngine.h"

//External Dependencies
#include <SDL3/SDL.h>
//#include <SDL_ttf.h>

using namespace std;

int main(int argc, char** argv) {

	GameEngine* engine = GameEngine::getInstance();

	while( engine->running() )
	{
		engine->setStartFrame();
		
		engine->handleEvents();
		engine->update();
		engine->render();
	}
	
	engine->destroyEngine();
	system("pause");

	return 0;
}