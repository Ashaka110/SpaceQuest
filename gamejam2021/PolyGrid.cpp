#include "PolyGrid.h"

PolyGrid::PolyGrid()
{
	scroll = 0;
	offset = 0;
	for (int x = 0; x < 50; x++)
	{
		for (int y = 0; y < 50; y++) {
			noise[x][y] = rand() % 10 / 10.0f; 
		}
	}

}

void PolyGrid::render(Camera * camera)
{
	float planeHeight = -10;

	float scale = 4;
	float gridnum = 50;


	for (int x = 0; x < gridnum; x++)
	{
		for (int y = 0; y < gridnum; y++)
		{
			float diff = ((x+y) * 1.5) < 100? ((x+y) * 1.5) :100;
			diff = diff > 0 ? diff : 0;
			sf::Color gridColor(100-diff, 100-diff, 100-diff);

			Point r = Point(x*scale, planeHeight, ((float)y - scroll)*scale);
			Point a = Point::add(Point(0, noise[x][(y+1+offset)%50], scale), r);
			Point b = Point::add(Point(scale, noise[x+1][(y+offset)%50], 0), r);

			r = Point::add(Point(0, noise[x][(y+offset)%50], 0), r);

			Point rb = Point(-x*scale, planeHeight, ((float)y - scroll)*scale);
			Point ab = Point::add(Point(0, noise[x][(y+1+offset)%50], scale), rb);
			Point bb = Point::add(Point(-scale, noise[x+1][(y+offset)%50], 0), rb);

			rb = Point::add(Point(0, noise[x][(y+offset)%50], 0), rb);

			camera->drawLine(r, a, gridColor);
			camera->drawLine(r, b, gridColor);
			camera->drawLine(rb, ab, gridColor);
			camera->drawLine(rb, bb, gridColor);
		}
	}
}

void PolyGrid::update(float delta)
{
	scroll += delta * 4;
	  
	if (scroll > 1) {
		scroll -= 1;
		offset++;
	}
}
