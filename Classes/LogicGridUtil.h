#ifndef __LOGICGRID_H__
#define __LOGICGRID_H__
#include "cocos2d.h"

struct LogicGrid
{
	int x;
	int y;
	LogicGrid(int x = 0, int y = 0) : x(x), y(y){}
	//*
	bool operator == (const LogicGrid &grid)const
	{
		return grid.x == x && grid.y == y;
	}
	bool operator != (const LogicGrid &grid)const
	{
		return (x != grid.x || y != grid.y);
	}
};

static bool isValidGrid(const LogicGrid &grid)
{
	bool isValidX = grid.x >= 0 && grid.x < COlUMNS_SIZE;
	bool isValidY = grid.y >= 0 && grid.y < ROWS_SIZE;
	return isValidX && isValidY;
}

static std::vector<LogicGrid> getSquareGrids(const LogicGrid& grid, int distance)
{
	std::vector<LogicGrid> grids;
	int minX = grid.x - distance;
	int maxX = grid.x + distance;
	int minY = grid.y - distance;
	int maxY = grid.y + distance;
	for (int i = minX; i <= maxX; ++i)
	{
		for (int j = minY; j <= maxY; ++j)
		{
			auto temp = LogicGrid(i, j);
			if (isValidGrid(temp))
			{
				grids.push_back(temp);
			}
		}
	}

	return grids;
}

#endif
