#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <SFML/Graphics.hpp>
#include "cube.h"
#include "camera.h"
#include "point.h"
#include "cubeGrid.h"

class TestScene{
    public:
        TestScene();
        void render(Camera *c);
        void update(float delta);

    private:
        Cube cubes[5][5][5];
        CubeGrid grid;
        

};

#endif // TESTSCENE_H
