#include "Grid.h"


Grid::Grid(int cols, int rows, int window_res_x, int window_res_y) : gridSize{cols, rows}
{

	cells.resize(rows);
	cell initialcell;

	cells.resize(rows);

	for (int i{ 0 }; i < rows; ++i)
	{
		cells[i].resize(cols, initialcell);
	}

	for(int i{0}; i<rows; ++i)
	{
		for (int j{ 0 }; j < cols; ++j)
		{
			cells[i][j].pos = glm::vec3((float(j / cols) + float(1.0f / cols) / 2.0f) - 1, -(float(i / rows) + float(1.0f / rows) / 2.0f) + 1, 0.0f);
		}
	}
}

void Grid::flipCell(cell* c)
{
	c->state = !c->state;
}

void Grid::bornCell(cell* c)
{
	c->state = true;
}

void Grid::killCell(cell* c)
{
	c->state = false;
}

vector<vector<cell>> Grid::getCells()
{
	return this->cells;
}

array<int, 2> Grid::getSize()
{
	return { gridSize[0], gridSize[1] };
}