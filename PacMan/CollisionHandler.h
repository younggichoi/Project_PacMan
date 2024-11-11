//
//  CollisionHandler.h
//  Mission11
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

#include "CollisionDetector.h"

class CollisionHandler
{
public:
    void operator()(PacMan& pacman, const Map& map);
    void operator()(PacMan& pacman, Ghost& ghost);
};
