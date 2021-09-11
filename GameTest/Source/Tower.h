#ifndef _TOWER_H
#define _TOWER_H

#include "Enemy.h"
#include "CollisionManager.h"

struct Projectile
{
	float x = 0.0f;
	float y = 0.0f;
	float dirx = 0.0f;
	float diry = 0.0f;
	float angle = 0.0f;

	// enemy that is being shot at
	EnemyPtr e;

	std::shared_ptr<CSimpleSprite> sprite;

	bool collided = false;

	bool out_of_bounds()
	{
		return (fabs(x) >= APP_VIRTUAL_WIDTH || fabs(y) >= APP_VIRTUAL_HEIGHT);
	}
};

class Tower
{
public:

	Tower(Grid& _grid, Cell& _cell, float _speed, float _range, int _dam, int _frame, float _tta, float _pr, char* _char, float _r, float _g, float _b)
		: grid(&_grid), location(_cell), speed(_speed), range(_range), damage(_dam), frame(_frame), time_to_attack(_tta), proj_rad(_pr), c(_char), r(_r), g(_g), b(_b) 
	{
		xOff = (float)grid->get_cell_width() / 2;
		yOff = (float)grid->get_cell_height() / 2;

		attack_timer = time_to_attack;
	}

	void draw();

	void shoot(EnemyPtr& e, float delta);

	virtual void update_projectiles();

	bool check_if_hit(EnemyPtr& e);

	float get_range() { return range; }
	float get_projectile_radius() { return proj_rad;  }
	float get_x() { return (float)location.x;  }
	float get_y() { return (float)location.y; }
	bool is_sold() { return sold; }
	Cell get_cell() { return location; }

protected:
	std::vector< Projectile > projectiles;
	float speed;
	float range;
	int damage;
	Cell location;
	Grid* grid;
	float r, g, b;
	char* c;
	int frame;
	float time_to_attack;
	float proj_rad;
	float attack_timer = 0.0;
	bool sold = false;
	float xOff, yOff;
};

typedef std::unique_ptr<Tower> TowerPtr;

#endif
