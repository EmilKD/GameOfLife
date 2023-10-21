#include "Grid.h"

void Grid::flipCell(cell *c) 
{
	c->state = !c->state;
}

void Grid::bornCell(cell *c) 
{
	c->state = true;
}

void Grid::killCell(cell *c) 
{
	c->state = false;
}

Grid::Grid()
{
	for(int i{0}; i<this->gridSize; ++i)
	{
		for (int j{ 0 }; j < this->gridSize; ++j)
		{
			cells[i][j].pos = glm::vec3(500 * i + 250, 500 * j + 250, 0.0f);
		}
	}
}