#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>
#include<array>
#include "Graphics.h"

using std::vector, std::array;

struct cell
{
	glm::vec3 pos{0.0f, 0.0f, 0.0f};
	bool state{ false };
	int id;
};

class Grid
{
	
public:
	Grid(int cols, int rows, int window_res_x, int window_res_y);
	array<int, 2> getSize();
	vector<vector<cell>> getCells();
	void checkNeighbors(GraphicalObj* gobj, float scale_x, float scale_y);
	int getAliveNeighborsCount(int cellNum);
	cell* getCellByID(int id);

	int step{ 0 };

private:
	const int gridSize[2]{10, 10};
	vector<vector<cell>> cells;
	vector<cell*> cellPtrs;
	Colors color;
};

