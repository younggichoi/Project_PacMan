//
//  Map.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Map.h"

Map::Map(){
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

void Map::createMap() {
    
    // Blue Plastic
    Material block_mtl;
    block_mtl.setEmission(0.0f, 0.0f, 0.2f, 1.0f);
    block_mtl.setAmbient(0.0f, 0.0f, 0.2f, 1.0f);
    block_mtl.setDiffuse(0.0f, 0.0f, 0.6f, 1.0f);
    block_mtl.setSpecular(0.6f, 0.6f, 0.6f, 1.0f);
    block_mtl.setShininess(30.0f);
    
    float x = LEFT_BOUNDARY;
    float y = TOP_BOUNDARY;
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].setCenter(x + i * BLOCK_SIZE, y - j * BLOCK_SIZE, 0.0f);
            blocks[i][j].setWidth(BLOCK_SIZE);
            blocks[i][j].setHeight(BLOCK_SIZE);
            blocks[i][j].setMTL(block_mtl);
            
            // 가장자리
            if( i == 0 || i == blocks.size() - 1 || j == 0 || j == blocks[i].size() - 1){
                blocks[i][j].setPassable(false);
            }
            else if ( (i==2 || i==3 || i==5 || i==6) && (j==2 || j==3 || j==5 || j==6)){
                blocks[i][j].setPassable(false);
            }
            else{
                blocks[i][j].setPassable(true);
            }
            
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
