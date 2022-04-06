//Extra Lib Includes
#include <iostream>
#include <string>

//Internal Dependencies
#include "Game/engine/GameEngine.h"

//External Dependencies
#include <SDL.h>
#include <SDL_ttf.h>

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