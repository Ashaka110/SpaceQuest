#include "PolyShip.h"

PolyShip::PolyShip()
{
	position = Point(0, -3, 4);
	angle = 0;
}

void PolyShip::render(Camera * camera)
{

	//       3
	//
	//		4 5
	//
	//		 0
	//       
	// 1			2

	Point verts[6] = {
		Point(0,0,0),
		Point(-1,0,-.5),
		Point(1,0,-.5),
		Point(0,0,1),
		Point(0, -.25f, .3f),
		Point(0, .25f, .3f)
	};

	Point::RotateZ(verts, 6, angle);
	Point::Translate(verts, 6, position);


	camera->drawLine(verts[0], verts[1]);
	camera->drawLine(verts[0], verts[2]);
	camera->drawLine(verts[3], verts[1]);
	camera->drawLine(verts[3], verts[2]);
	camera->drawLine(verts[4], verts[1]);
	camera->drawLine(verts[4], verts[2]);
	camera->drawLine(verts[5], verts[1]);
	camera->drawLine(verts[5], verts[2]);
	camera->drawLine(verts[0], verts[4]);
	camera->drawLine(verts[0], verts[5]);
	camera->drawLine(verts[3], verts[4]);
	camera->drawLine(verts[3], verts[5]);
}

void PolyShip::update(float delta)
{
	angle += delta;



}
