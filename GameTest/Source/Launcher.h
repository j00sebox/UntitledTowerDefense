#ifndef _LAUNCHER_H
#define _LAUNCHER_H

#include "Tower.h"

class Launcher : public Tower
{

public:
	Launcher(Grid& _grid, Cell& _cell)
		: Tower(_grid, _cell, 0.1f, 500.0f, 150, 11, 5000.0f, 10.0f, "L", 0.7f, 0.7f, 0.7f)
	{}

	void update_projectiles() override
	{
		// remove projectiles that are offscreen or have collided with an enemy
		projectiles.erase(
			std::remove_if(
				projectiles.begin(),
				projectiles.end(),
				[](Projectile& p) { return (p.out_of_bounds() || p.collided); }
		), projectiles.end());

		// update positions
		for (Projectile& p : projectiles)
		{
			if (!p.e->is_dead())
			{
				p.dirx = (p.e->get_x() - p.x) * speed;
				p.diry = (p.e->get_y() - p.y) * speed;

				p.angle = atan2(p.diry, p.dirx) - PI / 2;

				p.x += p.dirx;
				p.y += p.diry;

				p.sprite->SetPosition(p.x + xOff, p.y + yOff);
				p.sprite->SetAngle(p.angle);
			}
			else
			{
				p.collided = true;
			}
			
		}
	}
};

#endif
