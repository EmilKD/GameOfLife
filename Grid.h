#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>
#include<array>

using std::vector, std::array;

struct cell
{
	glm::vec3 pos{0.0f, 0.0f, 0.0f};
	bool state{ false };
};

class Grid
{
	

public:
	Grid(int cols, int rows, int window_res_x, int window_res_y);
	void flipCell(cell *c);
	void bornCell(cell *c);
	void killCell(cell *c);
	array<int, 2> getSize();
	vector<vector<cell>> getCells();

private:
	const int gridSize[2]{10, 10};
	vector<vector<cell>> cells;
	int step{ 0 };
};

