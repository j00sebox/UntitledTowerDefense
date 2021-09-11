#include "Enemy.h"

float Enemy::speed_modifier = 0.0f;
int Enemy::damage_modfier = 0;
int Enemy::healh_modifier = 0;

Enemy::Enemy(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid, int _health, int _frame, int _dam, int _worth, float _rad, float _tta, float _speed) :
	x(_x), y(_y), path(_path), base(&_base), grid(&_grid), health(_health), frame(_frame), damage(_dam), worth(_worth), radius(_rad), time_to_attack(_tta), speed(_speed)
{
	// create sprite for enemey
	sprite = std::unique_ptr<CSimpleSprite>( App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12) );
	sprite->SetPosition(x, y);
	sprite->SetFrame(frame);
	sprite->SetScale(1.0f);

	// offset are used to show the enemy in the center of the cell
	xOff = grid->get_cell_width() / 2;
	yOff = grid->get_cell_height() / 2;

	// add any diffuculty modifiers to base values
	health += healh_modifier;
	damage += damage_modfier;
	speed += speed_modifier;

	// the enemy attacks as soon as it reaches the goal
	attack_timer = time_to_attack;
}

void Enemy::move(float delta)
{
	// reached goal so enemy can attack base
	if (counter >= path.size())
	{
		attack_timer += delta;

		if (attack_timer >= time_to_attack)
		{
			attack();
			attack_timer = 0.0f;
		}

		return;
	}

	// distant from the current position of the enemy to the start of the next cell
	float xdist = 0.0;
	float ydist = 0.0;

	// if the next cell is still reachable
	if ( ( grid->in_path(path[counter]) || grid->is_base(path[counter]) ))
	{
		xdist = path[counter].x - x;
		ydist = path[counter].y - y;
		
	}
	// otherwise enemies need to turn around
	else
	{
		backtrack(path[counter - 1]);
		xdist = path[counter].x - x;
		ydist = path[counter].y - y;
	}

	// get angle of direction offset by 90 degrees
	angle = atan2(ydist, xdist) - PI/2;

	// if the distance is close enough the enemy will snap to the next cell
	if (fabs(xdist) <= speed && fabs(ydist) <= speed)
	{
		x = path[counter].x;
		y = path[counter].y;
		grid->set_traversing(path[counter], false);
		counter++;
		if(counter < path.size())
			grid->set_traversing(path[counter], true);
	}
	// otherwise increase the position by some increment
	else
	{
		if (fabs(xdist) > 0)
		{
			x += (xdist / fabs(xdist)) * speed;
		}

		if (fabs(ydist) > 0)
		{
			y += (ydist / fabs(ydist)) * speed;
		}
	}

	// update sprite postion
	update_pos();
}

void Enemy::take_damage(int _dam)
{
	if ( (health - _dam) > 0)
	{
		health -= _dam;
	}
	else
	{
		health = 0;
		dead = true;

		// if enemy dies need to set the current cell to not be traversing anymore
		if (counter < path.size())
			grid->set_traversing(path[counter], false);

		// using the sell function to add the value of the dead enemy
		base->sell(worth);
		base->increment_kills();
	}
}


// changes the current path the enemy is following
void Enemy::update_path(std::vector<Cell>& _p)
{
	branch_ind = get_branch(_p);

	// don't update path if the enemy has already comitted to it
	if ( (branch_ind == -1) || (branch_ind > counter) )
		path = _p;
}

// this returns at what point the new path and old path split off
int Enemy::get_branch(std::vector<Cell>& _p)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (_p[i] != path[i])
		{
			return i;
		}
	}

	// path hasn't changed
	return -1;
}

// recalculate path in order to turn around
void Enemy::backtrack(Cell& _c)
{
	// the new start cell becomes the previous cell
	std::unordered_map<Cell, Cell> map;
	Cell goal = *(base->get_cell());

	Search::a_star(*grid, _c, goal, map);

	path = Search::get_path(map, _c, goal);

	// reset counter
	counter = 1;
}