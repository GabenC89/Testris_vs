#pragma once

#define TILE_SIZE 40

#include <iostream>
#include <map>
#include <string>

//Internal Includes
#include "../main/Block.h"
#include "../main/GameBoard.h"

//SDL Includes
#include <SDL.h>
#include <SDL_ttf.h>

template<typename T>
void draw(T& t, int sx, int sy) {}
//Draw functions
template void draw<GameBoard>(GameBoard& board, int sx, int sy);
template void draw<Block>(Block& b, int sx, int sy);
template<typename T, typename U>
void draw(T& t, U u, int sx, int sy) {}
template void draw<TTF_Font, std::string>(TTF_Font& gameFont, std::string text, int sx, int sy);

class RenderEngine 
{
	static RenderEngine* engine;
	SDL_Renderer* gameRenderer;

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;

	int frameCount;
	uint32_t frameStart;
	int frameTime;

	int startPosX;
	int windowWidth, windowHeight;

	void drawBackground();
	bool init(SDL_Window* window, int w, int h);
protected:
	RenderEngine(SDL_Window* window, int w, int h);
	~RenderEngine();
public:
	RenderEngine(RenderEngine& engine) = delete;
	void operator=(const RenderEngine& engine) = delete;

	static RenderEngine* getInstance(SDL_Window* window, int w, int h);
	void destroyEngine();
	
	void drawFrameForNextBlock(int sx, int sy, int w, int h);
	//void drawScore();
	void draw(GameBoard& board, int sx, int sy);
	void draw(Block& b, int sx, int sy);
	void draw(TTF_Font& gameFont, std::string text, int sx, int sy);
	void drawBoardFrame(GameBoard& board);

	void increaseFrameCount();
	int getFrameCount();

	void clearRenderedScreen();
	void delayFrame();
	void finalizeScene();
	void setStartFrame();
};