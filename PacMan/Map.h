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
#include "Vector3f.h"
#include "Sphere.h"

using namespace std;

class Map{
public:
    Map();
    void createMap(const std::string&);
    const Block& getBlock(int c, int r) const;
    const Dot& getDot(int c, int r) const;
    void draw() const;
    void setBlockColor(float r, float g, float b);
    void setDotColor(float r, float g, float b);

private:
    array<array<Block, NUM_ROW>, NUM_COL> blocks;
    array<array<Dot, NUM_ROW>, NUM_COL> dots;
    Vector3f block_color;
    Vector3f dot_color;
};
