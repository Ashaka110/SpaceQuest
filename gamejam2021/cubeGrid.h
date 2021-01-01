#ifndef CUBEGRID_H
#define CUBEGRID_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "point.h"
#include "camera.h"
#define gridSize 10

class CubeGrid{
    public:
        CubeGrid();
        void render(Camera *camera);
        void update(float delta);

        void drawSide(Point a, Point b);
        void drawLine(Point a, Point b);
        void drawCube(Point a);

        int getBlock(float x, float y, float z);
        int getBlock(int x, int y, int z);



    private:

        int grid[gridSize][gridSize][gridSize];

};

#endif // CUBEGRID_H
