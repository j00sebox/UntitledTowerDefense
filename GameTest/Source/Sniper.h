#ifndef _SNIPER_H
#define _SNIPER_H

#include "Tower.h"

class Sniper : public Tower
{

public:
	Sniper(Grid& _grid, Cell& _cell)
		: Tower(_grid, _cell, 0.1f, 1000.0f, 90, 19, 3500.0f, 10.0f, "S", 0.0f, 0.5f, 0.7f)
	{}
};

#endif