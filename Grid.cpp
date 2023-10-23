#include "Grid.h"
#include<iostream>

Grid::Grid(int cols, int rows, int window_res_x, int window_res_y) : gridSize{cols, rows}
{

	cells.resize(rows);
	cell initialcell;
	int counter{ 0 };

	for (int i{ 0 }; i < rows; ++i)
	{
		cells[i].resize(cols, initialcell);
	}

	for (int i{ 0 }; i < rows; ++i)
	{
		for (int j{ 0 }; j < cols; ++j)
		{
			//std::cout << "x: " << j / 20.0f + 1.0f / 20.0f / 2.0f << " y: " << i / 10.0f + 1.0f / 10.0f / 2.0f << std::endl;
			this->cells[i][j].pos = glm::vec3(2*(j / float(cols) + 1.0f / float(cols) / 2.0f) - 1, -2*(i / float(rows) + 1.0f / float(rows) / 2.0f) + 1, 0.0f);
			this->cells[i][j].id = counter;
			counter++;
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

cell Grid::getCellByID(int id)
{
	for(vector<cell> vc: this->cells)
	{
		for(cell c: vc)
			if (c.id == id)
				return c;
	}
	std::cout << "cell with specified id not found";
}

vector<cell> Grid::getNeighbors(int cellNum)
{
	//get all neighbors of cell c
	vector<cell> neighbors;
	int grid_x = this->getSize()[1];
	int grid_y = this->getSize()[0];

	// [1]  [2]  [3]
	// [4]  [-]  [5]
	// [6]  [7]  [8]
	int n1, n2, n3, n4, n5, n6, n7, n8;
	n1 = cellNum - grid_x - 1;
	n2 = cellNum - grid_x;
	n3 = cellNum - grid_x + 1;
	n4 = cellNum - 1;
	n5 = cellNum + 1;
	n6 = cellNum + grid_x - 1;
	n7 = cellNum + grid_x;
	n8 = cellNum + grid_x + 1;

	if (n1 < 0) 
	{
		n1 += grid_x * grid_y;
	}
	else if(n1 > (grid_x*grid_y))
	{
		std::cout << "";
	}
	if (n2 < 0)
	{
		n2 += grid_x * grid_y;
	}
	else if (n2 > (grid_x * grid_y))
	{
		n2 -= grid_x * grid_y;
	}
	if (n3 < 0)
	{
		n3 += grid_x * grid_y;
	}
	else if (n3 > (grid_x * grid_y))
	{
		n3 -= grid_x * grid_y;
	}
	if (n4 < 0)
	{
		n4 += grid_x * grid_y;
	}
	else if (n4 > (grid_x * grid_y))
	{
		n4 -= grid_x * grid_y;
	}
	if (n5 < 0)
	{
		n5 += grid_x * grid_y;
	}
	else if (n5 > (grid_x * grid_y))
	{
		n5 -= grid_x * grid_y;
	}
	if (n6 < 0)
	{
		n6 += grid_x * grid_y;
	}
	else if (n6 > (grid_x * grid_y))
	{
		n6 -= grid_x * grid_y;
	}
	if (n7 < 0)
	{
		n7 += grid_x * grid_y;
	}
	else if (n7 > (grid_x * grid_y))
	{
		n7 -= grid_x * grid_y;
	}
	if (n8 < 0)
	{
		n8 += grid_x * grid_y;
	}
	else if (n8 > (grid_x * grid_y))
	{
		n8 -= grid_x * grid_y;
	}

	vector<cell> vc;

	vc.push_back(getCellByID(n1));
	vc.push_back(getCellByID(n2));
	vc.push_back(getCellByID(n3));
	vc.push_back(getCellByID(n4));
	vc.push_back(getCellByID(n5));
	vc.push_back(getCellByID(n6));
	vc.push_back(getCellByID(n7));
	vc.push_back(getCellByID(n8));

	return vc;
}

void Grid::checkNeighbors(cell *c)
{
	vector<cell> neighbors = getNeighbors(c->id);
	int aliveNeighbors{ 0 };

	// if alive -> lives if 2 or 3 neighbors are alive -> alive
	// if 3 neighbors alive then -> born
	for (cell c : neighbors) 
	{
		if (c.state)
			aliveNeighbors++;
	}
	
	if (c->state)
	{
		if (aliveNeighbors == 2 || aliveNeighbors == 3)
		{
			c->state = 1;
		}
		else
		{
			c->state = 0;
		}
	}
	else if (aliveNeighbors == 3) 
	{
		c->state = 1;
	}
}


