#include <iostream>
#include "testscene.h"

TestScene::TestScene(){
    std::cout << "TestScene\n";
    
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            for(int z = 0; z < 5; z++){
                cubes[x][y][z].Position = Point(x,y,z);
            }
        }
    }


}

void TestScene::render(Camera *camera){

    camera->drawCube(Point(0,0,5));
    camera->drawCube(Point(2,0,5));
    camera->drawCube(Point(-2,0,3));
    camera->drawCube(Point(2,5,5));
    camera->drawCube(Point(-3,0,5));
    camera->drawCube(Point(-3,0,10));
    camera->drawCube(Point(-5,0,10));
    camera->drawCube(Point(-5,4,10));
    camera->drawCube(Point(-5,4,12));
/*
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            for(int z = 0; z < 5; z++){
                cubes[x][y][z].render(camera);
            }
        }
    }
    */

    //grid.render(camera);
}

void TestScene::update(float delta){
    
}
