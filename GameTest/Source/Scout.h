#ifndef _SCOUT_H
#define _SCOUT_H

#include "Enemy.h"

class Scout : public Enemy
{
public:
	Scout(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid)
											// health, frame, damage, worth, radius, time to attack, speed
		: Enemy(_x, _y, _path, _base, _grid,	60,		2,		15,		15,		10.0f,	1500.0f,	3.0f)
	{}
};

#endif 
