#ifndef _BLASTER_H
#define _BLASTER_H

#include "Tower.h"

class Blaster : public Tower
{

public:
	Blaster(Grid& _grid, Cell& _cell)
		: Tower(_grid, _cell, 0.1f, 50.0f, 100, 15, 2000.0f, 10.0f, "B", 0.7f, 0.3f, 0.0f)
	{}
};

#endif