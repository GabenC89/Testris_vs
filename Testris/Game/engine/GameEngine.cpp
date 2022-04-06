#include "GameEngine.h"

GameEngine* GameEngine::engine = nullptr;

GameEngine::GameEngine()
{
	if (!init())
	{
		delete board;
		destroyEngine();
	}
	else
	{
		isRunning = true;
		createGameBoard();
	}
}

GameEngine::~GameEngine()
{
	destroyEngine();
}

GameEngine* GameEngine::getInstance()
{
	if (engine == nullptr)
	{
		engine = new GameEngine();
	}
	return engine;
}

void GameEngine::calculateCurrentScore(int multiplier)
{
	while(multiplier >= 0)
	{
		currentScore += (std::pow(2, multiplier) * LINE_SCORE);
		multiplier--;
	}
	if (currentScore >= currentLevel * LEVELUP_SCORE && levelSpeed > 5)
	{
		currentLevel++;
		levelSpeed = levelSpeed - 5;
		if (levelSpeed < 5) levelSpeed = 5;
	}
	std::cout << "Score: " << currentScore << std::endl;
}

void GameEngine::createGameBoard()
{
	board = new GameBoard();
	startPosX = (board->getWidth() / 2) - 1;
	currentScore = 0;
	currentLevel = 1;
	levelSpeed = 80; //Frames to autoFall trigger
}

void GameEngine::createNewBlock()
{
	if(currentBlock == nullptr)
	{
		if (nextBlock == nullptr)
		{
			createNextBlock();
		}
		currentBlock = move(nextBlock);
		createNextBlock();
	}

	if (!currentBlock->tryMoveDown(*board))
	{
		currentBlock = nullptr;
		board->gameOver();
	}
}

void GameEngine::createNextBlock()
{
	srand(time(nullptr));
	bool reversed = rand() % 2;
	int type = rand() % 5;
	nextBlock = new Block(type, startPosX, reversed);
}

bool GameEngine::createGameWindow()
{
	windowWidth = DEFAULT_GRID_W * 2 * TILE_SIZE;
	windowHeight = DEFAULT_GRID_H * TILE_SIZE;
	if (needFullScreenStartup)
	{
		gameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	}
	else 
	{
		gameWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	}
	if (gameWindow == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool GameEngine::getRendererInstance()
{
	//Create Renderer
	gameRenderer = RenderEngine::getInstance(gameWindow, windowWidth, windowHeight);
	if (gameRenderer == nullptr)
	{
		return false;
	}
	return true;
}

void GameEngine::destroyBlocks()
{
	delete currentBlock;
	delete nextBlock;
}

void GameEngine::destroyGameObjects()
{
	destroyBlocks();
	delete board;
}

void GameEngine::destroyEngine()
{
	destroyBlocks();
	destroyRenderObjects();
	TTF_Quit();
	SDL_Quit();
	GameEngine::engine = nullptr;
}

void GameEngine::destroyRenderObjects()
{
	if (gameFont != nullptr)
	{
		TTF_CloseFont(gameFont);
	}
	if (gameRenderer != nullptr)
	{
		gameRenderer->destroyEngine();
	}
	if (gameWindow != nullptr)
	{
		SDL_DestroyWindow(gameWindow);
	}
}

/*

void GameEngine::drawFrameForNextBlock()
{
	SDL_Surface* text;
	SDL_Color textColor = { 255, 255, 255 };

	text = TTF_RenderText_Solid(gameFont, "NEXT", textColor);
	if (!text) {
		cout << "Failed to render text: " << TTF_GetError() << endl;
	}

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(gameRenderer, text);

	int posX = (DEFAULT_GRID_W + (startPosX - 1)) * TILE_SIZE;
	int posY = 2 * TILE_SIZE;
	SDL_Rect dest = { posX , posY, text->w, text->h };

	SDL_RenderCopy(gameRenderer, text_texture, NULL, &dest);
}

void GameEngine::drawScore()
{
	SDL_Surface* text;
	SDL_Color textColor = { 255, 255, 255 };

	std::string label= "Score: ";
	std::string scoreText = label + std::to_string(currentScore);
	text = TTF_RenderText_Solid(gameFont, scoreText.c_str(), textColor);
	if (!text) {
		cout << "Failed to render text: " << TTF_GetError() << endl;
	}

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(gameRenderer, text);

	int posX = (DEFAULT_GRID_W + (startPosX - 1)) * TILE_SIZE;
	int posY = 10 * TILE_SIZE;
	SDL_Rect dest = { posX , posY, text->w, text->h };

	SDL_RenderCopy(gameRenderer, text_texture, NULL, &dest);
}

*/

void GameEngine::handleEvents()
{
	keyDown = keyLeft = keyRight = keyUp = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) isRunning = false;
		switch (event.type) 
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_DOWN:
						keyDown = 1;
						break;
					case SDLK_LEFT:
						keyLeft = 1;
						break;
					case SDLK_RIGHT:
						keyRight = 1;
						break;
					case SDLK_UP:
						keyUp = 1;
						break;
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
		}
	}
}

void GameEngine::drawGameStateFrame()
{
	std::string nextText = "NEXT";
	int alignX = (board->getWidth() + (startPosX - 1)) * TILE_SIZE;
	int alignY = 4 * TILE_SIZE;
	int nWidth = 4 * TILE_SIZE;
	int nHeight = 4 * TILE_SIZE;
	gameRenderer->drawFrameForNextBlock(alignX, alignY, nWidth, nHeight);
	gameRenderer->draw(*gameFont, nextText, alignX, 3 * TILE_SIZE);
	if (nextBlock != nullptr)
	{
		int centeringLeft = alignX - ((startPosX - 1) * TILE_SIZE / 2) - (nWidth / 2);
		gameRenderer->draw(*nextBlock, centeringLeft, alignY);
	}

	//Draw Score
	std::string label = "Score: ";
	std::string scoreText = label + std::to_string(currentScore);
	gameRenderer->draw(*gameFont, scoreText, alignX, 10 * TILE_SIZE);
}

bool GameEngine::init()
{
	bool createSuccess = false;
	//Initialize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
		return false;
	}

	gameFont = TTF_OpenFont("./fonts/GROBOLD.ttf", 24);
	if (gameFont == nullptr) {
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
		return false;
	}

	if (createGameWindow())
	{
		createSuccess = getRendererInstance();
	}

	return createSuccess;
}

void GameEngine::render()
{
	gameRenderer->clearRenderedScreen();
	
	gameRenderer->draw(*board, 0, 0);
	gameRenderer->drawBoardFrame(*board);
	if (currentBlock != nullptr)
	{
		gameRenderer->draw(*currentBlock, 0, 0);
	}
	drawGameStateFrame();

	gameRenderer->delayFrame();
	gameRenderer->finalizeScene();
}

bool GameEngine::running()
{
	return isRunning;
}

void GameEngine::setStartFrame()
{
	gameRenderer->setStartFrame();
}

void GameEngine::update()
{
	gameRenderer->increaseFrameCount();

	if (!board->isGameOver())
	{
		if (keyLeft) currentBlock->tryMoveLeft(*board);
		if (keyRight) currentBlock->tryMoveRight(*board);
		if (keyUp) currentBlock->tryRotate(*board);

		if (keyDown || gameRenderer->getFrameCount() % levelSpeed == 0)
		{
			if (!currentBlock->tryMoveDown(*board))
			{
				int multiplier = board->checkCurrentScoreLines(currentBlock->getPosY(), currentBlock->getHeight());
				calculateCurrentScore(multiplier - 1);
				currentBlock = nullptr;
			}
		}

		if (currentBlock == nullptr)
		{
			createNewBlock();
		}
	}
	//std::cout << "Frames drawn: " << frameCount << std::endl;
}