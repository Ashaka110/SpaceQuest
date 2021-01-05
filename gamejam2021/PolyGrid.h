#pragma once
#include "point.h"
#include "camera.h"

#define gridSize 10
//#define gridSize 10

class PolyGrid
{
    public:
		PolyGrid();
		PolyGrid(float height, float scale);
		void render(Camera *camera);
		void update(float delta);

		//Point position;
		float scrollSpeed;
	private:

		float noise[50][50];

		float planeHeight;
		float scroll;
		int offset;
		float hscale;

		float timer;
        //int grid[gridSize][gridSize][gridSize];
};

