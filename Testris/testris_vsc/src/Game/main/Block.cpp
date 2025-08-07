#include "Block.h"

Color::Color(char flag, int r, int g, int b, int t) :
	gridFlag(flag),
	red(r),
	green(g),
	blue(b),
	transparency(t)
{}

//Block methods

Block::Block(int type, GameBoard& b, int sx, bool needReverse, bool needGhost) :
	shape(blueprints[type]),
	gridPosX(sx),
	gridPosY(0),
	showGhost(needGhost),
	size(max(shape.size(), shape[0].size()))
{
	if (needReverse)
	{
		reverseCols(shape);
	}
	color = colors[type];
	calculateGhostPosition(b);
}

bool Block::checkCollision(GameBoard& b, int posx, int posy, vector< vector<bool> > checkedShape)
{
	int width = checkedShape.size();
	int height = checkedShape[0].size();

	vector < vector<char> > grid = b.getGrid();
	if (posx < 0 || posx + width - 1 >= b.getWidth() || posy + height - 1 >= b.getHeight())
	{
		return true;
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (checkedShape[i][j] && grid[posx + i][posy + j] != 'X')
			{	
				return true;
			}
		}
	}
	return false;
}

bool Block::checkCollisionForRotate(GameBoard& b, int posx, int posy, vector< vector<bool> > shape)
{
	if (checkCollision(b, posx, posy, shape))
	{
		if (posx + shape.size() - 1 >= b.getWidth())
		{
			int overlap = posx + shape.size() - b.getWidth();
			bool success = tryMoveLeft(b, overlap);
			return !success;
		}
		return true;
	}
	return false;
	
}

Color Block::getColor()
{
	return color;
}

int Block::getPosX()
{
	return gridPosX;
}

int Block::getGhostPosX()
{
	return ghostPosX;
}

int Block::getPosY()
{
	return gridPosY;
}

int Block::getGhostPosY()
{
	return ghostPosY;
}

bool Block::isGhostNeeded()
{
	return showGhost;
}

vector< vector<bool> > Block::getShapeForm()
{
	return shape;
}

int Block::getWidth()
{
	return shape.size();
}

int Block::getHeight()
{
	return shape[0].size();
}

void Block::reverseCols(vector< vector<bool> >& mtx)
{
	if (min(mtx.size(), mtx[0].size()) > 1)
	{
		vector< vector<bool> > tmpShape = mtx;
		for (int i = 0; i < mtx.size(); i++)
		{
			for (int j = 0; j < mtx[i].size() / 2; j++)
			{
				int col = mtx[i].size() - j - 1;
				tmpShape[i][j] = mtx[i][col];
				tmpShape[i][col] = mtx[i][j];
			}
		}
		mtx = tmpShape;
	}
}

void Block::transpose(vector< vector<bool> >& mtx)
{
	vector< vector<bool> > tmpShape(mtx[0].size(), vector<bool>(mtx.size()));
	for (int i = 0; i < tmpShape.size(); i++)
	{
		for (int j = 0; j < tmpShape[i].size(); j++)
		{
			tmpShape[i][j] = mtx[j][i];
		}
	}

	mtx.resize(tmpShape.size(), vector<bool>(tmpShape[0].size()));
	mtx = tmpShape;
}

bool Block::tryMoveDown(GameBoard& b)
{
	int tmpPosY = gridPosY + 1;
	if ( !checkCollision(b, gridPosX, tmpPosY, shape) )
	{
		gridPosY = tmpPosY;
		return true;
	}
	b.addBlock(color.gridFlag, gridPosX, gridPosY, shape);
	return false;
}

bool Block::tryMoveLeft(GameBoard& b, int by)
{
	int tmpPosX = gridPosX - by;
	if (!checkCollision(b, tmpPosX, gridPosY, shape))
	{
		gridPosX = tmpPosX;
		calculateGhostPosition(b);
		
		return true;
	}
	return false;
}

void Block::tryMoveRight(GameBoard& b)
{
	int tmpPosX = gridPosX + 1;
	if (!checkCollision(b, tmpPosX, gridPosY, shape))
	{
		gridPosX = tmpPosX;
		calculateGhostPosition(b);
	}
}

void Block::tryRotate(GameBoard& b)
{
	vector< vector<bool> > tmpShape = shape; 

	transpose(tmpShape);
	reverseCols(tmpShape);
	
	if ( !checkCollisionForRotate(b, gridPosX, gridPosY, tmpShape) )
	{
		shape = tmpShape;
		calculateGhostPosition(b);
	}
}

void Block::calculateGhostPosition(GameBoard& b)
{
	ghostPosX = gridPosX;
	ghostPosY = 0;
	while (!checkCollision(b, ghostPosX, ghostPosY, shape))
	{
		ghostPosY++;
	}
	ghostPosY--;
}