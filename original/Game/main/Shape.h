#pragma once

#include <vector>
#include "GameBoard.h"

using namespace std;

class Shape 
{
protected:
	const vector< vector< vector<bool> > > blueprints =
	{
		{	//I Shape
			{1, 1, 1, 1}
		},
		{	//O Shape
			{1, 1},
			{1, 1}
		},
		{	//T Shape
			{1, 1, 1},
			{0, 1, 0}
		},
		{	//J Shape
			{1, 1, 1},
			{0, 0, 1}
		},
		{	//S Shape
			{0, 1, 1},
			{1, 1, 0}
		}
	};

	virtual void reverseCols(vector< vector<bool> >& mtx) = 0;
	virtual void transpose(vector< vector<bool> >& mtx) = 0;
public:
	virtual ~Shape() {}

	virtual bool tryMoveDown(GameBoard& b) = 0;
	virtual bool tryMoveLeft(GameBoard& b, int by = 1) = 0;
	virtual void tryMoveRight(GameBoard& b) = 0;
	virtual void tryRotate(GameBoard& b) = 0;

};
