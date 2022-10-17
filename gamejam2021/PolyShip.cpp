#include "PolyShip.h"

PolyShip::PolyShip()
{
	position = Point(0, -2, 4);
	shieldPosition = Point(0, -2, 4);
	targetPosition = Point(0, -3, 4);
	angle = 0;
	shieldAngle = 0;
	shieldTimer = 0;
	//hasShield = true;
	shieldSpawnTimer = 3;
	//startRespawn();
}

void PolyShip::render(Camera * camera)
{
	if (respawnTimer > 2) {
		
		for (int i = 0; i < 12; i++)
		{
			camera->drawLine(shipdestroy[i*2], shipdestroy[(i * 2)+1]);
		}
	}

	//       3
	//
	//		4 5
	//
	//		 0
	//       
	// 1			2

	if (visible) {
		if (hasShield && (shieldSpawnTimer < 0 || ((int)(shieldSpawnTimer * 8) % 2) == 1)) {


			Point sverts[12] = {
				Point(0.15f,    0.1f,  1.1f),	//0
				Point(0.15f,   -0.22f,  1.1f),    //1
				Point(-0.15f,  -0.22f,  1.1f),    //2
				Point(-0.15f,   0.1f,  1.1f),    //3

				Point(1.1f,-.1f,-0.6f),    //4
				Point(1.1f, .1f,-0.6f),    //5
				Point(.15f, .4f, 0.2f),    //6
				Point(-.15f, .4f, 0.2f),    //7
				Point(-1.1f, .1f, -0.6f),    //8
				Point(-1.1f,-.1f, -0.6f),    //9
				Point(-.15f,-.4f, 0.2f),    //10
				Point(.15f,-.4f, 0.2f),    //11
			};

			float colorCurve = (cos(3*shieldTimer)/4.0f  + 3.0f/4.0f);
			if (shieldSpawnTimer > 0) {
				colorCurve = 1;
			}
			Point::RotateZ(sverts, 12, shieldAngle);
			//Point::Scale(sverts, 12, 1.2);
			Point::Translate(sverts, 12, Point::add(shieldPosition, Point(0, 0, 0)));


			sf::Color shieldColor = sf::Color(0, 150 * colorCurve, 255 * colorCurve);
			sf::Color outershieldColor = sf::Color(0, 75 * colorCurve * 1.0, 128 * colorCurve * 1.0);


			camera->drawLine(sverts[0], sverts[1], shieldColor);
			camera->drawLine(sverts[1], sverts[2], shieldColor);
			camera->drawLine(sverts[2], sverts[3], shieldColor);
			camera->drawLine(sverts[3], sverts[0], shieldColor);

			camera->drawLine(sverts[4], sverts[5], outershieldColor);
			camera->drawLine(sverts[5], sverts[6], outershieldColor);
			camera->drawLine(sverts[6], sverts[7], outershieldColor);
			camera->drawLine(sverts[7], sverts[8], outershieldColor);
			camera->drawLine(sverts[8], sverts[9], outershieldColor);
			camera->drawLine(sverts[9], sverts[10], outershieldColor);
			camera->drawLine(sverts[10], sverts[11], outershieldColor);
			camera->drawLine(sverts[11], sverts[4], outershieldColor);

			camera->drawLine(sverts[0], sverts[5], shieldColor, outershieldColor);
			camera->drawLine(sverts[0], sverts[6], shieldColor, outershieldColor);

			camera->drawLine(sverts[1], sverts[4], shieldColor, outershieldColor);
			camera->drawLine(sverts[1], sverts[11], shieldColor, outershieldColor);

			camera->drawLine(sverts[2], sverts[9], shieldColor, outershieldColor);
			camera->drawLine(sverts[2], sverts[10], shieldColor, outershieldColor);

			camera->drawLine(sverts[3], sverts[7], shieldColor, outershieldColor);
			camera->drawLine(sverts[3], sverts[8], shieldColor, outershieldColor);

			/*
			*/


		}

	Point verts[6] = {
		Point( 0,    0,  0),	//0
		Point(-1,    0,-.5f),    //1
		Point( 1,    0,-.5f),    //2
		Point( 0,    0,  1),    //3
		Point( 0,-.25f,.3f),    //4
		Point( 0, .25f,.3f)     //5
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
}



void PolyShip::update(float delta)
{

	shieldSpawnTimer -= delta;
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		startRespawn();
	}
	*/
	//angle += delta;
	shieldTimer += delta;

	Point diff = Point::add(targetPosition, Point::scale(position, -1));
	position = Point::add(position, Point::scale(diff, delta *5));
	Point shieldDiff = Point::add(targetPosition, Point::scale(shieldPosition, -1));
	shieldPosition = Point::add(shieldPosition, Point::scale(shieldDiff, delta *5));

	float sqrDist = diff.x; // Point::sqrDistance(diff, Point(0,0,0));

	targetAngle = sqrDist  ;
	angle = angle + (targetAngle - angle )*delta*3  ;
	shieldAngle = shieldAngle + (shieldDiff.x - shieldAngle )*delta*3  ;

	if (angle > 3.14/2) {
		angle -= 3.14;
	}else
	if (angle < -3.14/2) {
		angle += 3.14;
	}
	if (shieldAngle > 3.14/2) {
		shieldAngle -= 3.14;
	}else
	if (shieldAngle < -3.14/2) {
		shieldAngle += 3.14;
	}

	if (respawnTimer > 0) {
		respawnTimer -= delta;
		visible = false;
		if (respawnTimer <1) {
			//hasShield = true;

			visible = ((int)(respawnTimer * 32) % 2) == 1;

		}
		if (respawnTimer > 2) {

			for (int i = 0; i < 12; i++)
			{
				Point a = shipdestroy[i * 2];
				Point b = shipdestroy[i * 2 + 1];

				Point center = Point::getCenter(a, b);
				Point offset = Point::scale(Point::add(center, Point::scale(position, -1)), delta * 8);
				shipdestroy[i * 2] = Point::add(a, offset);
				shipdestroy[i * 2 + 1] = Point::add(b, offset);
				shipdestroy[i * 2] = Point::RotateAroundZ(shipdestroy[i * 2], center, (delta  + i * .05) * (i%2==1?-1:1));
				shipdestroy[i * 2 +1] = Point::RotateAroundZ(shipdestroy[i * 2+1], center, (delta+ i * .05) * (i%2==1?-1:1));
			}
		}
	}
	else {
		visible = true;
	}

}

bool PolyShip::isAlive()
{
	return respawnTimer <=0;
}

void PolyShip::startRespawn()
{
	respawnTimer = 3;

	shipdestroy[0] = Point(0, 0, 0);	//0
	shipdestroy[1] = Point(-1, 0, -.5);    //1
	shipdestroy[2] = Point(0, 0, 0);	//0
	shipdestroy[3] = Point(1, 0, -.5);    //2
	shipdestroy[4] = Point(0, 0, 1);    //3
	shipdestroy[5] = Point(-1, 0, -.5);    //1
	shipdestroy[6] = Point(0, 0, 1);    //3
	shipdestroy[7] = Point(1, 0, -.5);    //2

	shipdestroy[8] = Point(0, -.25f, .3f);    //4
	shipdestroy[9] = Point(-1, 0, -.5);    //1
	shipdestroy[10] = Point(0, -.25f, .3f);    //4
	shipdestroy[11] = Point(1, 0, -.5);    //2
	shipdestroy[12] = Point(0, .25f, .3f);    //5
	shipdestroy[13] = Point(-1, 0, -.5);    //1
	shipdestroy[14] = Point(0, .25f, .3f);    //5
	shipdestroy[15] = Point(1, 0, -.5);    //2

	shipdestroy[16] = Point(0, 0, 0);	//0
	shipdestroy[17] = Point(0, -.25f, .3f);    //4
	shipdestroy[18] = Point(0, 0, 0);	//0
	shipdestroy[19] = Point(0, .25f, .3f);    //5
	shipdestroy[20] = Point(0, 0, 1);    //3
	shipdestroy[21] = Point(0, -.25f, .3f);    //4
	shipdestroy[22] = Point(0, 0, 1);    //3
	shipdestroy[23] = Point(0, .25f, .3f);    //5

	Point::RotateZ(shipdestroy, 24, angle);
	Point::Translate(shipdestroy, 24, position);

}
