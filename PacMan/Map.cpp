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
    float x = LEFT_BOUNDARY;
    float y = TOP_BOUNDARY;
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].setCenter(x + i * BLOCK_SIZE, y - j * BLOCK_SIZE, 0.0f);
            blocks[i][j].setWidth(BLOCK_SIZE);
            blocks[i][j].setHeight(BLOCK_SIZE);
            blocks[i][j].setColor(block_color);
            dots[i][j].setCenter(x + i * BLOCK_SIZE, y - j * BLOCK_SIZE, 0.0f);
            dots[i][j].setColor(dot_color);
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
            blocks[col][row].setPassable(false);
            dots[col][row].setEaten(true);
            col++;
            break;
        case '1':
            blocks[col][row].setPassable(true);
            dots[col][row].setEaten(true);
            col++;
            break;
        case '2':
            blocks[col][row].setPassable(true);
            dots[col][row].setEaten(false);
            col++;
            break;
        case '3':
            blocks[col][row].setPassable(true);
            dots[col][row].setEaten(false);
            dots[col][row].setDotsize(Dot::DOTSIZE::LARGE);
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


const Block& Map::getBlock(int c, int r) const{
    return blocks[c][r];
}

const Dot& Map::getDot(int c, int r) const
{
    return dots[c][r];
}

void Map::draw() const{
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            getBlock(i, j).draw();
            getDot(i, j).draw();
        }
    }
}

void Map::setBlockColor(float r, float g, float b) {
    block_color.setPos(r, g, b);
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) 
            blocks[i][j].setColor(block_color);
    }
}

void Map::setDotColor(float r, float g, float b) {
    dot_color.setPos(r, g, b);
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++)
            dots[i][j].setColor(dot_color);
    }
}