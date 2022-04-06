#include "GameBoard.h"

GameBoard::GameBoard(int w, int h) :
	gridWidth(w),
	gridHeight(h),
	gameFinished(false)
{
	cleanBoard();
}

void GameBoard::addBlock(char c, int posx, int posy, vector< vector<bool> > shape)
{
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if(shape[i][j])
			{
				int bX = posx + i;
				int bY = posy + j;
				grid[bX][bY] = c;
			}
		}
	}
}

bool GameBoard::checkCurrentLine(int y)
{
	for (int x = 0; x < gridWidth; x++)
	{
		if (grid[x][y] == 'X')
			return false;
	}
	return true;
}

int GameBoard::checkCurrentScoreLines(int posy, int depth)
{
	int minDepth = posy;
	int maxDepth = minDepth + depth;
	vector<int> scoreLines;
	int scoredLinesNum = 0;

	for (int y = minDepth; y < maxDepth; y++)
	{
		if (checkCurrentLine(y))
		{
			scoreLines.push_back(y);
			scoredLinesNum++;
		}
	}

	if (scoredLinesNum > 0)
	{
		//increaseScore(scoreLines.size());
		clearScoredLines(scoreLines, maxDepth);
	}
	return scoredLinesNum;
}

void GameBoard::cleanBoard()
{
	grid.resize(gridWidth);
	for (int i = 0; i < gridWidth; i++)
	{
		grid[i].resize(gridHeight);
		for (int j = 0; j < gridHeight; j++)
		{
			grid[i][j] = 'X';
		}
	}
}

void GameBoard::clearScoredLines(vector<int> lines, int maxDepth)
{
		for (int y : lines)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				grid[x][y] = 'X';
			}
		}
		dropRemainingBlocks(maxDepth - 1, lines.size());

}

void GameBoard::dropRemainingBlocks(int checkDepth, int maxDrop)
{
	for (int y = checkDepth; y > 0; y--)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (grid[x][y] != 'X')
			{
				int fallY = y + 1;
				while ( (fallY - y) < maxDrop && grid[x][fallY] == 'X')
				{
					fallY++;
				}
				grid[x][fallY] = grid[x][y];
				grid[x][y] = 'X';
			}
		}
	}
}

void GameBoard::gameOver()
{
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			if (grid[i][j] != 'X')
			{
				grid[i][j] = 'W';
			}
		}
	}
	gameFinished = true;
}

bool GameBoard::isGameOver()
{
	return gameFinished;
}

vector< vector<char> > GameBoard::getGrid()
{
	return grid;
}

int GameBoard::getWidth()
{
	return gridWidth;
}

int GameBoard::getHeight()
{
	return gridHeight;
}
