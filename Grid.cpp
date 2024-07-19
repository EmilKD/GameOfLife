#include<iostream>
#include<random>
#include<functional>
#include "Grid.h"


bool randomBool() {
	static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
	return gen();
}

Grid::Grid(int cols, int rows, int window_res_x, int window_res_y) : gridSize{cols, rows}
{

	cells.resize(rows);
	cell initialcell;
	initialcell.state = 1;
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
			if((counter > cols*rows/2.0f - cols*rows/10.0f) || (counter < cols * rows / 10.0f + cols * rows / 10.0f))
				this->cells[i][j].state = 0;
			else
				this->cells[i][j].state = randomBool();
			counter++;

			cellPtrs.push_back(&cells[i][j]);
		}
	}



	/*for (vector<cell> vc : cells) {
		for (cell c : vc)
			std::cout << c.id << " ";
		std::cout << std::endl;
	}*/
}

vector<vector<cell>> Grid::getCells()
{
	return cells;
}

array<int, 2> Grid::getSize()
{
	return { gridSize[0], gridSize[1] };
}

cell* Grid::getCellByID(int id)
{
	return cellPtrs[id];
	std::cout << "cell with specified id not found";
	return nullptr;
}

int Grid::getAliveNeighborsCount(int cellNum)
{
	//get all neighbors of cell c
	vector<cell> neighbors;
	int grid_x = this->getSize()[0];
	int grid_y = this->getSize()[1];

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
	else if(n1 >= (grid_x*grid_y))
	{
		n1 -= grid_x * grid_y;
	}
	if (n2 < 0)
	{
		n2 += grid_x * grid_y;
	}
	else if (n2 >= (grid_x * grid_y))
	{
		n2 -= grid_x * grid_y;
	}
	if (n3 < 0)
	{
		n3 += grid_x * grid_y;
	}
	else if (n3 >= (grid_x * grid_y))
	{
		n3 -= grid_x * grid_y;
	}
	if (n4 < 0)
	{
		n4 += grid_x * grid_y;
	}
	else if (n4 >= (grid_x * grid_y))
	{
		n4 -= grid_x * grid_y;
	}
	if (n5 < 0)
	{
		n5 += grid_x * grid_y;
	}
	else if (n5 >= (grid_x * grid_y))
	{
		n5 -= grid_x * grid_y;
	}
	if (n6 < 0)
	{
		n6 += grid_x * grid_y;
	}
	else if (n6 >= (grid_x * grid_y))
	{
		n6 -= grid_x * grid_y;
	}
	if (n7 < 0)
	{
		n7 += grid_x * grid_y;
	}
	else if (n7 >= (grid_x * grid_y))
	{
		n7 -= grid_x * grid_y;
	}
	if (n8 < 0)
	{
		n8 += grid_x * grid_y;
	}
	else if (n8 >= (grid_x * grid_y))
	{
		n8 -= grid_x * grid_y;
	}


	return int(cellPtrs[n1]->state) 
		+ int(cellPtrs[n2]->state)
		+ int(cellPtrs[n3]->state)
		+ int(cellPtrs[n4]->state)
		+ int(cellPtrs[n5]->state)
		+ int(cellPtrs[n6]->state)
		+ int(cellPtrs[n7]->state)
		+ int(cellPtrs[n8]->state);
}

void Grid::checkNeighbors(GraphicalObj* gobj, float scale_x, float scale_y)
{
	cell* tempC{NULL};
	int aliveNeighbors{ 0 };

	for (int i{0}; i<gridSize[1]* gridSize[0]; ++i)
	{
		tempC = cellPtrs[i];
	
		aliveNeighbors = getAliveNeighborsCount(tempC->id);

		// if alive -> lives if 2 or 3 neighbors are alive -> alive
		// if 3 neighbors alive then -> born
	
		if (tempC->state)
		{
			if(aliveNeighbors < 2)
			{
				tempC->state = 0;
			}
			else if(aliveNeighbors > 3)
			{
				tempC->state = 0;
			}
		}
		else if (aliveNeighbors == 3) 
		{
			tempC->state = 1;
		}
			
		// Rendering
		gobj->transform(glm::vec3(scale_x, scale_y, 0.0f), tempC->pos);
		if (tempC->state)
			gobj->DrawShape(color.Amber);
		else
			gobj->DrawShape(color.Black);
		
	}
}


