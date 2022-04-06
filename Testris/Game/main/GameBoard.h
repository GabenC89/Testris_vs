#pragma once

#define DEFAULT_GRID_W 10
#define DEFAULT_GRID_H 20

#include <vector>

using namespace std;

class GameBoard {
	bool gameFinished, isShown;
	vector< vector<char> > grid;
	int gridWidth, gridHeight;

public:
	GameBoard(int w = DEFAULT_GRID_W, int h = DEFAULT_GRID_H);
	virtual ~GameBoard() {}

	void addBlock(char c, int posx, int posy, vector< vector<bool> > shape);
	bool checkCurrentLine(int y);
	int checkCurrentScoreLines(int posy, int depth);
	void cleanBoard();
	void clearScoredLines(vector<int> lines, int maxDepth);
	void dropRemainingBlocks(int checkDepth, int maxDrop);
	void gameOver();
	bool isGameOver();

	vector< vector<char> > getGrid();
	int getWidth();
	int getHeight();
};