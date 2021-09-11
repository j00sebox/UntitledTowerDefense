#ifndef _REAVER_H
#define _REAVER_H

#include "Enemy.h"

class Reaver : public Enemy
{
public:
	Reaver(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid)
											// health, frame, damage, worth,   radius, time to attack, speed
		: Enemy(_x, _y, _path, _base, _grid,	100,	0,		10,		10,		20.0f,	3000.0f,	1.15f)
	{}
};

#endif 
