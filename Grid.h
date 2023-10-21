#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>
#include<array>

using std::vector;

struct cell
{
	glm::vec3 pos;
	bool state{ false };
};

class Grid
{

public:
	Grid();
	void flipCell(cell *c);
	void bornCell(cell *c);
	void killCell(cell *c);

private:
	static const int gridSize{10};
	cell cells[gridSize][gridSize];
	int step{ 0 };
};

