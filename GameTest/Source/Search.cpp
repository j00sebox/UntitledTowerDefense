#include "Search.h"

bool Search::a_star(const Grid& g, const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& conn)
{
	PriorityQueue fringe;
	std::unordered_map<Cell, float> cellCost;
	float cost = 0.0f;
	bool goalFound = false;

	// no initial cost
	fringe.push(cost, start);
	cellCost[start] = cost;
	conn[start] = start;

	std::unordered_set<Cell> reached;
	reached.insert(start);

	while (!fringe.empty())
	{
		Cell current = fringe.top();

		// reached the base so we don't need to check other nodes
		if (current == g.base)
		{
			goalFound = true;
			break;
		}

		for (Cell next : g.neighbours(current))
		{
			// if the cell has not been reached yet
			if (reached.find(next) == reached.end())
			{
				if (next == goal) goalFound = true;
				cellCost[next] = cellCost[current] + 1.0f;
				cost = cellCost[next] + heuristic(next, goal);
				fringe.push(cost, next);
				reached.insert(next);
				conn[next] = current;
			}
		}
	}

	return goalFound;
}

std::vector<Cell> Search::get_path(std::unordered_map<Cell, Cell>& conn, Cell start, Cell goal)
{
	std::vector<Cell> path;
	Cell current = goal;

	while (current != start)
	{
		path.push_back(current);
		current = conn[current];
	}

	path.push_back(start);

	std::reverse(path.begin(), path.end());

	return path;
}