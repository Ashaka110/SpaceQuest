#pragma once
#include "point.h"
#include "camera.h"

#define gridSize 10
//#define gridSize 10

class PolyGrid
{
    public:
		PolyGrid();
		void render(Camera *camera);
		void update(float delta);

		//Point position;
	private:

		float noise[50][50];

		float scroll;
		int offset;
        //int grid[gridSize][gridSize][gridSize];
};

