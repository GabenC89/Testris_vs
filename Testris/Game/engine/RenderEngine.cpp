#include "RenderEngine.h"

RenderEngine* RenderEngine::engine = nullptr;

RenderEngine::RenderEngine(SDL_Window* window, int w, int h) :
	windowWidth(w),
	windowHeight(h),
	frameCount(0)
{
	if (!init(window,w,h))
	{
		destroyEngine();
	}
}

RenderEngine::~RenderEngine()
{
	destroyEngine();
}


void RenderEngine::destroyEngine()
{
	if (gameRenderer != nullptr)
	{
		SDL_DestroyRenderer(gameRenderer);
	}
	engine = nullptr;
}

RenderEngine* RenderEngine::getInstance(SDL_Window* window, int w, int h)
{
	if (engine == nullptr)
	{
		engine = new RenderEngine(window,w,h);
	}
	return engine;
}

bool RenderEngine::init(SDL_Window* window, int w, int h) {
	//Create Renderer
	gameRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gameRenderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void RenderEngine::clearRenderedScreen()
{
	SDL_RenderClear(gameRenderer);
	drawBackground();
}

void RenderEngine::delayFrame()
{
	frameTime = SDL_GetTicks() - frameStart;

	if (FRAME_DELAY > frameTime)
	{
		SDL_Delay(FRAME_DELAY - frameTime);
	}
}

void RenderEngine::drawBackground()
{
	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = windowWidth;
	bgRect.h = windowHeight;
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(gameRenderer, &bgRect);
}

void RenderEngine::draw(Block& b, int sx, int sy)
{
	SDL_Rect blockPiece;
	blockPiece.w = TILE_SIZE;
	blockPiece.h = TILE_SIZE;
	vector< vector<bool> > form = b.getShapeForm();
	Color color = b.getColor();
	for (int i = 0; i < form.size(); i++)
	{
		for (int j = 0; j < form[i].size(); j++)
		{
			if (form[i][j])
			{
				blockPiece.x = sx + ((b.getPosX() + i) * TILE_SIZE);
				blockPiece.y = sy + ((b.getPosY() + j) * TILE_SIZE);
				SDL_SetRenderDrawColor(gameRenderer, color.red, color.green, color.blue, color.transparency);
				SDL_RenderFillRect(gameRenderer, &blockPiece);
				SDL_SetRenderDrawColor(gameRenderer, 200, 200, 200, 255);
				SDL_RenderDrawRect(gameRenderer, &blockPiece);
			}
		}
	}
}

void RenderEngine::draw(GameBoard& board, int sx, int sy)
{
	const map<char, Color> colorScheme =
	{
		{'X', Color()},
		{'W', Color('W', 50, 50, 50)},
		{'C', Color('C', 0, 255, 255)},
		{'Y', Color('Y', 255, 255, 0)},
		{'M', Color('M', 255, 0, 255)},
		{'B', Color('B', 0, 0, 255)},
		{'G', Color('G', 0, 255, 0)}
	};
	SDL_Rect gridPiece;
	gridPiece.w = TILE_SIZE;
	gridPiece.h = TILE_SIZE;

	vector< vector<char> > grid = board.getGrid();
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			gridPiece.x = sx + (i * TILE_SIZE);
			gridPiece.y = sy + (j * TILE_SIZE);
			char colorCode = grid[i][j];
			Color color = colorScheme.at(colorCode);
			SDL_SetRenderDrawColor(gameRenderer, color.red, color.green, color.blue, color.transparency);
			SDL_RenderFillRect(gameRenderer, &gridPiece);

			if (colorCode != 'X')
			{
				SDL_SetRenderDrawColor(gameRenderer, 200, 200, 200, 255);
				SDL_RenderDrawRect(gameRenderer, &gridPiece);
			}
		}
	}
}

void RenderEngine::draw(TTF_Font& gameFont, std::string t, int sx, int sy)
{
	SDL_Surface* text;
	SDL_Color textColor = { 255, 255, 255 };

	text = TTF_RenderText_Solid(&gameFont, t.c_str(), textColor);
	if (!text) {
		cout << "Failed to render text: " << TTF_GetError() << endl;
	}

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(gameRenderer, text);

	int posX = sx;
	int posY = sy;
	SDL_Rect dest = { posX , posY, text->w, text->h };

	SDL_RenderCopy(gameRenderer, text_texture, NULL, &dest);
}

void RenderEngine::drawBoardFrame(GameBoard& board)
{
	SDL_Rect frameRect;
	frameRect.x = 0;
	frameRect.y = 0;
	frameRect.w = board.getWidth() * TILE_SIZE;
	frameRect.h = board.getHeight() * TILE_SIZE;
	SDL_SetRenderDrawColor(gameRenderer, 200, 200, 200, 255);
	SDL_RenderDrawRect(gameRenderer, &frameRect);
}

void RenderEngine::drawFrameForNextBlock(int sx, int sy, int width, int height)
{
	SDL_Rect frameRect;
	frameRect.x = sx;
	frameRect.y = sy;
	frameRect.w = width;
	frameRect.h = height;
	SDL_SetRenderDrawColor(gameRenderer, 200, 200, 200, 255);
	SDL_RenderDrawRect(gameRenderer, &frameRect);
}

void RenderEngine::finalizeScene()
{
	SDL_RenderPresent(gameRenderer);
}

void RenderEngine::increaseFrameCount()
{
	frameCount++;
}

int RenderEngine::getFrameCount()
{
	return frameCount;
}

void RenderEngine::setStartFrame()
{
	frameStart = SDL_GetTicks();
}