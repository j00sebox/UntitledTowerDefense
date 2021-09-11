#ifndef _BASE_H
#define _BASE_H

#include "stdafx.h"
#include "GameOverManager.h"
#include "Grid.h"

struct HealthBar
{
	float healthx = 100.0;
	float healthy = 700.0;
	float xOff = 200;
	float yOff = 30;
};

class Base
{
public:

	Base(Cell& _cell) : location(&_cell) { hb = new HealthBar; }

	~Base() { delete hb; }

	bool buy(int _m)
	{
		if ((money - _m) >= 0)
		{
			money -= _m;
			return true;
		}

		return false;
	}

	void sell(int _m)
	{
		money += _m;
	}

	void take_damage(int _dam);
	void update_healthbar();
	void display_money();
	void display_kills();

	void increment_kills() { kills++; }

	Cell* get_cell() { return location; }

private:

	int health = 100;
	int money = 30;
	int kills = 0;

	Cell* location;

	char money_buff[12] = "";
	char kills_buff[12] = "";

	HealthBar* hb;
};

#endif
