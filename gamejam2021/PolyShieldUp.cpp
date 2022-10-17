#include "PolyShieldUp.h"

PolyShieldUp::PolyShieldUp()
{
	animationTimer = 0;
	direction = Point(0, 0, -3);
	alive = false;
	collectionTimer = 0;
}

void PolyShieldUp::render(Camera * camera)
{
	if (alive || collectionTimer > 0) {

			float colorCurve = (cos(3*animationTimer)/4.0f  + 3.0f/4.0f);
			sf::Color shieldColor = sf::Color(0, 150 * colorCurve, 255 * colorCurve);
			sf::Color outershieldColor = sf::Color(0, 75 * colorCurve * 1.0, 128 * colorCurve * 1.0);

			Point cverts[12] = {
				Point(1,       0,  0),	//0
				Point(.866,   .5,  0),	//2
				Point(.5,   .866,  0),	//0
				Point(0,       1,  0),	//0
				Point(-.5,  .866,  0),	//0
				Point(-.866,  .5,  0),	//0
				Point(-1,      0,  0),	//0
				Point(-.866,- .5,  0),	//0
				Point(-.5, -.866,  0),	//0
				Point(0,      -1,  0),	//0
				Point(.5,  -.866,  0),	//0
				Point(.866,  -.5,  0),	//0
			};
			if (collectionTimer > 0) {
				Point::Scale(cverts, 12,collectionTimer>.75f?  1+ (1-collectionTimer) : (collectionTimer/.75 *1.25f));
				animationTimer += (1 - collectionTimer) * 2;
			}
			Point::Translate(cverts, 12, Point::add(position, Point(0, 0, 0)));
			for (int i = 0; i < 12; i++)
			{
				camera->drawLine(cverts[i], cverts[(i+1)%12], outershieldColor);
			}
			Point::Translate(cverts, 12, Point::scale( Point::add(position, Point(0, 0, 0)), -1));
			Point::RotateY(cverts, 12,  3.141 / 3);
			Point::Translate(cverts, 12, Point::add(position, Point(0, 0, 0)));
			for (int i = 0; i < 12; i++)
			{
				camera->drawLine(cverts[i], cverts[(i+1)%12], outershieldColor);
			}
			Point::Translate(cverts, 12, Point::scale( Point::add(position, Point(0, 0, 0)), -1));
			Point::RotateY(cverts, 12,  -3.141 / 3);
			Point::RotateX(cverts, 12,  3.141 / 2);
			Point::Translate(cverts, 12, Point::add(position, Point(0, 0, 0)));
			for (int i = 0; i < 12; i++)
			{
				camera->drawLine(cverts[i], cverts[(i+1)%12], outershieldColor);
			}
			Point::Translate(cverts, 12, Point::scale( Point::add(position, Point(0, 0, 0)), -1));
			Point::RotateZ(cverts, 12,  3.141 / 2 );
			Point::RotateY(cverts, 12,  3.141 / 3);
			Point::Translate(cverts, 12, Point::add(position, Point(0, 0, 0)));
			for (int i = 0; i < 12; i++)
			{
				camera->drawLine(cverts[i], cverts[(i+1)%12], outershieldColor);
			}


			Point pverts[12] = {
				Point( .5,       0,  0),	//0
				Point(.5,    .5f,  0),	//0
				Point(.25,    .433f,  0),	//0
				Point(0,     .4f,  0),	//0
				Point(-.25,   .433f,  0),	//0
				Point(-.5,   .5f,  0),	//0
				Point(-.5,      0,  0),	//0
				Point(-.4,- .4,  0),	//0
				Point(-.2, -.6,  0),	//0
				Point(0,      -.7,  0),	//0
				Point(.2,  -.6,  0),	//0
				Point(.4,  -.4,  0),	//0
			};

			if (collectionTimer > 0) {
				Point::Scale(pverts, 12, collectionTimer>.75f?  1 : (collectionTimer/.75));
			}
			Point::RotateY(pverts, 12, animationTimer);
			//Point::RotateZ(pverts, 12, shieldAngle);
			//Point::Scale(sverts, 12, 1.2);
			Point::Translate(pverts, 12, Point::add(position, Point(0, 0, 0)));


			colorCurve = (cos(3*animationTimer)/4.0f  + 3.0f/4.0f);
			shieldColor = sf::Color(0, 150 * colorCurve, 255 * colorCurve);
			outershieldColor = sf::Color(0, 75 * colorCurve * 1.0, 128 * colorCurve * 1.0);

			for (int i = 0; i < 12; i++)
			{
				camera->drawLine(pverts[i], pverts[(i+1)%12], shieldColor);
			}

	}

}

void PolyShieldUp::update(float delta)
{
	collectionTimer -= delta*2;
	if (alive) {
		animationTimer += delta;

		position = Point::add(position,Point::scale( direction, delta));
		if (position.z < -5) {
			alive = false;
		}
	}
}

bool PolyShieldUp::tryHit(Point pos)
{
	return false;
}

bool PolyShieldUp::canHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < 2) {
			alive = false;
			return true;
		}
	}
	return false;
}

int PolyShieldUp::getPointValue()
{
	return 200;
}

void PolyShieldUp::spawn(Point pos)
{
	alive = true;
	position = pos;
}
