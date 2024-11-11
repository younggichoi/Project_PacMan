//
//  Map.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Block.h"
#include <array>
#include "Constants.h"

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
