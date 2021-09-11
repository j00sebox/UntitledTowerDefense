#ifndef _BRUTE_H
#define _BRUTE_H

#include "Enemy.h"

class Brute : public Enemy
{
public:
	Brute(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid)
											// health, frame, damage, worth, radius, time to attack, speed
		: Enemy(_x, _y, _path, _base, _grid,	200,	 4,	    30,		50,   10.0f,    1500.0f,      0.9f)
	{}
};

#endif 