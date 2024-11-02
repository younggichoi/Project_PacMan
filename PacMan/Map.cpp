//
//  Map.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Map.h"


void Map::createMap() {
    float x = LEFT_BOUNDARY;
    float y = TOP_BOUNDARY;
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].setCenter(x + i * BLOCK_SIZE, y - j * BLOCK_SIZE, 0.0f);
            blocks[i][j].setWidth(BLOCK_SIZE);
            blocks[i][j].setHeight(BLOCK_SIZE);
        }
    }
}
const Block& Map::getBlock(int r, int c) const{
    return blocks[r][c];
}
void Map::draw() const{
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            getBlock(i, j).draw();
        }
    }
}
