//
//  Map.cpp
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include "Map.h"

Map::Map(){
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
        }
    }
}

void Map::createMap(const std::string& filename) {
    std::ifstream stageFile(filename);
    if (!stageFile.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }
    
    
    
    float x = LEFT_BOUNDARY;
    float y = TOP_BOUNDARY;

    
    std::string layout_start;
    while (getline(stageFile, layout_start))
    {
        if (layout_start == "//layout")
            break;
    }

    char param;
    int col = 0;
    int row = 0;
    while (stageFile.get(param))
    {
        switch (param)
        {
        case '0':
            blocks[row][col].setPassable(false);
            col++;
            break;
        case '1':
        case '2':
        case '3':
            blocks[row][col].setPassable(true);
            col++;
            break;
        case '\n':
            row++;
            col = 0;
            break;
        }
    }
    stageFile.close();
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
