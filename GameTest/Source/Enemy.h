#ifndef _ENEMY_H
#define _ENEMY_H

#include <memory>
#include <math.h>

#include "Base.h"
#include "Search.h"

class Enemy
{
public:

	Enemy(float _x, float _y, std::vector<Cell>& _path, Base& _base, Grid& _grid, int _health, int _frame, int _dam, int _worth, float _rad, float _tta, float _speed);

	void update_pos() { sprite->SetPosition(x + xOff, y + yOff); sprite->SetAngle(angle); }

	void update_path(std::vector<Cell>& _p);

	void attack() { base->take_damage(damage); }

	void backtrack(Cell& _c);

	void display() { sprite->Draw(); }

	void take_damage(int _dam);

	void move(float delta);

	int get_branch(std::vector<Cell>& _p);

	bool is_dead() { return dead; }

	float get_x() { return x; }
	float get_y() { return y; }

	float get_hit_radius() { return radius; }

	// used to increase difficulty of enemies
	static float speed_modifier;
	static int damage_modfier;
	static int healh_modifier;
	
private:

	float x, y;
	float xOff, yOff;
	int health;
	int frame;
	int damage;
	int worth;
	float radius;
	float time_to_attack;
	float speed;

	float angle = 0.0f;

	int branch_ind = -1;

	std::unique_ptr<CSimpleSprite> sprite;

	std::vector<Cell> path;

	Base* base;

	Grid* grid;

	float attack_timer;
	int counter = 1;
	bool dead = false;

};

typedef std::shared_ptr<Enemy> EnemyPtr;

#endif
