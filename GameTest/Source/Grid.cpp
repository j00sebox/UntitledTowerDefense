#include "Grid.h"

Grid::Grid(float cell_width, float cell_height) : cell_w(cell_width), cell_h(cell_height)
{
	numX = APP_VIRTUAL_WIDTH / (int)cell_w;
	numY = APP_VIRTUAL_HEIGHT / (int)cell_h;

	cells.resize(numX);

	for (int k = 0; k < numX; k++)
	{
		cells[k].resize(numY);
	}

	for (int i = 0; i < numX; i++)
	{
		for (int j = 0; j < numY; j++)
		{
			cells[i][j].x = i * cell_w;
			cells[i][j].y = j * cell_h;
		}
	}


	directions = {
		/* right, left, down, up */
		Cell{cell_w, 0}, Cell{-cell_w, 0},
		Cell{0, -cell_h}, Cell{0, cell_h}
	};

}

Cell* Grid::get_cell(const float& x, const float& y)
{
	int i = (int)floor(x / cell_w);
	int j = (int)floor(y / cell_h);

	if (0 < i && i < numX && 0 <= j && j < numY)
		return &cells[i][j];

	return nullptr;
}

std::vector<Cell> Grid::neighbours(Cell id) const
{
	std::vector<Cell> results;

	for (Cell d : directions)
	{
		Cell next{ id.x + d.x, id.y + d.y };

		if (in_bounds(next) && (in_path(next) || is_base(next)))
		{
			results.push_back(next);
		}
	}

	return results;
}

void Grid::draw_cell(float x, float  y, const float& r, const float& g, const float& b)
{

	float xOff = x + cell_w;
	float yOff = y + cell_h;

#if APP_USE_VIRTUAL_RES		
	APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
	APP_VIRTUAL_TO_NATIVE_COORDS(xOff, yOff);
#endif

	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(x, y);
	glVertex2f(xOff, y);
	glVertex2f(xOff, yOff);
	glVertex2f(x, yOff);
	glEnd();
}

void Grid::draw_grid()
{
	float startx = 0;
	float starty = 0;

	for (int y = 0; y < numY; y++)
	{
		for (int x = 0; x < numX; x++)
		{

			if (is_base(cells[x][y]))
			{
				draw_cell(cells[x][y].x, cells[x][y].y, 0.0f, 0.3f, 0.0f);
			}
			else if (in_path(cells[x][y]))
			{
				draw_cell(cells[x][y].x, cells[x][y].y, 0.3f, 0.3f, 0.3f);
			}
			else if (cells[x][y].occupied)
				continue;
			else
			{
				draw_cell(cells[x][y].x, cells[x][y].y, 0.5f, 0.5f, 0.5f);
			}

		}
	}

	for (int j = 0; j < numX; j++)
	{
		App::DrawLine(startx + cell_w, starty, startx + cell_w, starty + APP_VIRTUAL_HEIGHT, 1.0, 0.0, 0.0);
		startx += cell_w;
	}

	startx = 0;
	starty = 0;

	for (int j = 0; j < numY; j++)
	{
		App::DrawLine(startx, starty + cell_h, startx + APP_VIRTUAL_WIDTH, starty + cell_h, 1.0, 0.0, 0.0);
		starty += cell_h;
	}

}