#pragma once

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#include <iostream>
#include <math.h>
#include <string>

//Internal Includes
#include "RenderEngine.h"
#include "../main/Block.h"
#include "../main/GameBoard.h"

//SDL Includes
#include <SDL.h>
//#include <SDL_ttf.h>

class GameEngine
{
	const int LINE_SCORE = 100;
	const int LEVELUP_SCORE = 1000;

	void calculateCurrentScore(int multiplier);
	bool createGameWindow();
	void createGameBoard();
	void createNextBlock();
	void createNewBlock();
	bool getRendererInstance();
	void drawGameStateFrame();
	void destroyBlocks();
	void destroyGameObjects();
	void destroyRenderObjects();
	bool init();

	static GameEngine* engine;
	static int lastTime;

	SDL_Window* gameWindow;
	RenderEngine* gameRenderer;
	//TTF_Font* gameFont;

	const char* windowTitle = "Testris";
	int scaleSize = 2;
	
	GameBoard* board;
	Block* currentBlock;
	Block* nextBlock;
	bool isRunning;
	int currentLevel;
	int currentScore;
	int levelSpeed;
	bool needFullScreenStartup = false;
	int startPosX;
	int windowWidth, windowHeight;
	
	bool keyDown, keyLeft, keyRight, keyUp;

protected:
	GameEngine();
	~GameEngine();

public:
	GameEngine(GameEngine& engine) = delete;
	void operator=(const GameEngine& engine) = delete;

	static GameEngine* getInstance();

	void destroyEngine();
	void handleEvents();
	void render();
	bool running();
	void setStartFrame();
	void update();
};
