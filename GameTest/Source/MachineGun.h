#ifndef _MACH_GUN_H
#define _MACH_GUN_H

#include "Tower.h"

class MachineGun : public Tower
{

public:
	MachineGun(Grid& _grid, Cell& _cell) 
		: Tower(_grid, _cell, 0.1f, 200.0f, 30, 5, 500.0f, 10.0f, "M", 0.5f, 0.0f, 0.7f)
	{}
};

#endif
