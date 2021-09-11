#ifndef _DESTROYER_H
#define _DESTROYER_H

#include "Enemy.h"

class Destroyer : public Enemy
{
public:
	Destroyer(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid)
											// health, frame, damage, worth, radius, time to attack, speed
		: Enemy(_x, _y, _path, _base, _grid,	2000,	22,		100,  100,	  10.0f,	5000.0f,	  0.1f)
	{}
};

#endif 
