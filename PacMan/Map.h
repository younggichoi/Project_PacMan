//
//  Map.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#pragma once

#include "Block.h"
#include <array>
using namespace std;

#define NUM_COL = 320;
#define NUM_ROW = 320;
#define LEFT_BOUNDARY = -NUM_COL/2;
#define TOP_BOUNDARY = NUM_ROW/2

class Map{
public:
    Map();
    void createMap();
    const Block& getBlock(int r, int c) const;
    void draw() const;
private:
    array<array<Block, NUM_COL>, NUM_ROW> blocks;
    //std::array<std::array<Block, NUM_COL>, NUM_ROW> blocks;
};
