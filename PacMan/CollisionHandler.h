//
//  CollisionHandler.h
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "CollisionDetector.h"
#include "constant.h"

class CollisionHandler
{
public:
    void operator()(PacMan& pacman, Map& map);
    void operator()(PacMan& pacman, Ghost& ghost);
    void operator()(PacMan& pacman, Dot& dot);
    void operator()(Ghost& ghost, Map& map);
};
