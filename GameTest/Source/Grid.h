#ifndef _GRID_H
#define _GRID_H

#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <queue>
#include <time.h>

#include "app\app.h"

enum class SelectedTower
{
	MACHINE_GUN = 15,
	SNIPER = 30,
	BLASTER = 50,
	LAUNCHER = 100,
	NONE,
};

// basic unit of the grid
struct Cell
{
	float x, y;

	bool occupied = false;
	bool traversing = false;

	SelectedTower st = SelectedTower::NONE;

	Cell& operator=(const Cell& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	};

	bool operator==(const Cell& other) const
	{
		if (x == other.x && y == other.y)
			return true;
		return false;
	};

	bool operator<(const Cell& other) const
	{
		return std::tie(x, y) < std::tie(other.x, other.y);
	}

	bool operator!=(const Cell& other) const
	{
		if (x == other.x && y == other.y)
			return false;
		return true;
	}
};

namespace std {
	// need definition for hashing Cell
	template <> struct hash<Cell> {
		std::size_t operator()(const Cell& id) const noexcept {
			std::size_t hash = ((int)id.x ^ ((int)id.y));
			return hash;
		}
	};
}

class Grid
{
public:

	Grid(float cell_width, float cell_height);

	bool in_bounds(Cell _c) const
	{
		return (0 <= _c.x && _c.x < APP_VIRTUAL_WIDTH && 0 <= _c.y && _c.y < APP_VIRTUAL_HEIGHT);
	}

	bool in_path(Cell _c) const
	{
		return path.find(_c) != path.end();
	}

	bool is_base(Cell _c) const
	{
		return base == _c;
	}

	// this ensures cells cannot be removed from the path if an enemy is on it
	void set_traversing(Cell _c, bool _b)
	{
		Cell* c = get_cell(_c.x, _c.y);
		if(in_path(*c))
			c->traversing = _b;
	}

	void add_to_path(Cell _c) { path.insert(_c); }
	void remove_from_path(Cell _c) { path.erase(_c); }

	std::vector<Cell> neighbours(Cell _c) const;

	Cell* get_cell(const float& x, const float& y);

	void draw_cell(float x, float  y, const float& r, const float& g, const float& b);

	void draw_grid();

	float get_cell_width() { return cell_w; }
	float get_cell_height() { return cell_h; }

	std::vector< std::vector<Cell> > cells;

	Cell base;

	std::unordered_set<Cell> path;

private:

	// used to find the cells neighbours
	std::array<Cell, 4> directions;

	int numX, numY;

	float cell_w, cell_h;

};

#endif
