//
//  Map.h
//  Mission10
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Block.h"
#include <array>
#include <string>
#include "constant.h"

using namespace std;

class Map{
public:
    Map();
    void createMap(const std::string&);
    const Block& getBlock(int r, int c) const;
    void draw() const;
private:
    array<array<Block, NUM_COL>, NUM_ROW> blocks;
};
