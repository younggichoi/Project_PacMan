//
//  CollisionDetector.h
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "Sphere.h"
#include "Map.h"

#include <cmath>

class CollisionDetector
{
public:
    bool operator()(const PacMan& pacman, const Map& map);
    bool operator()(const PacMan& pacman, const Ghost& ghost);
    bool operator()(const PacMan& pacman, const Dot& dot);
};
