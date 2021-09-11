#ifndef _SEARCH_H
#define _SEARCH_H

#include "Grid.h"

class Search
{

public:

	// using manhattan distance
	static float heuristic(Cell a, Cell b) { return std::abs(a.x - b.x) + std::abs(a.y - b.y); }

	// performs an A* search on the grid
	static bool a_star(const Grid& g, const Cell& start, const Cell& goal, std::unordered_map<Cell, Cell>& conn);

	// reconstructs the path to the goal from the results of a_star()
	static std::vector<Cell> get_path(std::unordered_map<Cell, Cell>& conn, Cell start, Cell goal);

private:

	// underlying data structure for the A* search 
	struct PriorityQueue
	{
		// queue is sorted by the first element of this pair (cost)
		typedef std::pair<float, Cell> cellQ;
		std::priority_queue< cellQ, std::vector<cellQ>, std::greater<cellQ> > pq;

		// helper methods to make accessing the queue easier
		bool empty() { return pq.empty(); }

		void push(float priority, Cell c) { pq.emplace(priority, c); }

		Cell top()
		{
			Cell c = pq.top().second;
			pq.pop();
			return c;
		}
	};

};

#endif
