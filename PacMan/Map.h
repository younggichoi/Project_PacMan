//
//  Map.h
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#pragma once

#include "Constants.h"
#include "Block.h"
#include <array>
using namespace std;

class Map{
public:
    Map();
    void createMap();
    const Block& getBlock(int r, int c) const;
    void draw() const;
private:
    array<array<Block, NUM_COL>, NUM_ROW> blocks;
};
