#include "cubeGrid.h"
#include <iostream>

CubeGrid::CubeGrid(){
    std::cout << grid;
    for(int x = 0; x < gridSize; x++){
        for(int y = 0; y < gridSize; y++){
            for(int z = 0; z < gridSize; z++){
                grid[x][y][z] =  y < 1 ? 1 : 0;
                //if( y < 1 ){
                //}
            }
        }
    }
}



void CubeGrid::render(Camera *camera){
    for(int x = 0; x < gridSize; x++){
        for(int y = 0; y < gridSize; y++){
            for(int z = 0; z < gridSize; z++){
                if( getBlock(x,y,z) == 1){
                    camera->drawCube(Point(x,y,z));
                }
            }
        }
    }
}

void CubeGrid::drawSide(Point a, Point b){

}

int CubeGrid::getBlock(float x, float y, float z){

    return 0;
}

int CubeGrid::getBlock(int x, int y, int z){
          if(x < 0 || x > gridSize){
        return 0;
    }else if(y < 0 || y > gridSize){
        return 0;
    }else if(z < 0 || z > gridSize){
        return 0;
    }

    return grid[x][y][z];
}
