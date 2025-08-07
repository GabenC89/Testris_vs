#pragma once

#include <iostream>
#include <vector>

#include "Shape.h"


struct Color {
	char gridFlag;
	int red, green, blue;
	int transparency;

	Color(char flag = 'X', int r = 0, int g = 0, int b = 0, int t = 255);
	virtual ~Color() {}
};

class Block : Shape {
	Color color;
	const vector<Color> colors =
	{
		Color('C', 0, 255, 255),
		Color('Y', 255, 255, 0),
		Color('M', 255, 0, 255),
		Color('B', 0, 0, 255),
		Color('G', 0, 255, 0),
	};

	vector< vector<bool> > shape;
	int gridPosX, gridPosY;
	int ghostPosX, ghostPosY;
	bool showGhost;
	int size;

protected:
	bool checkCollision(GameBoard& b, int posx, int posy, vector< vector<bool> > shape);
	bool checkCollisionForRotate(GameBoard& b, int posx, int posy, vector< vector<bool> > shape);
	void reverseCols(vector< vector<bool> >& mtx);
	void transpose(vector< vector<bool> >& mtx);
public:
	Block(int type, GameBoard& b, int sx = 0, bool needReverse = false, bool needGhost = true);
	virtual ~Block() {}

	Color getColor();
	int getPosX();
	int getPosY();
	int getGhostPosX();
	int getGhostPosY();
	int getWidth();
	int getHeight();
	bool isGhostNeeded();
	vector< vector<bool> > getShapeForm();

	bool tryMoveDown(GameBoard& b);
	bool tryMoveLeft(GameBoard& b, int by = 1);
	void tryMoveRight(GameBoard& b);
	void tryRotate(GameBoard& b);
	void calculateGhostPosition(GameBoard& b);
};