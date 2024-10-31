//
//  Map.cpp
//  PacMan
//
//  Created by 이현우 on 10/31/24.
//

#include "Map.h"

void Map::createMap() {
    float x = LEFT_BOUNDARY;
    float y = TOP_BOUNDARY;
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].setCenter(x + i * BLOCK_SIZE, y - j * BLOCK_SIZE, 0.0f);
            blocks[i][j].setWidth(BLOCK_SIZE);
            blocks[i][j].setHeight(BLOCK_SIZE);
        }
    }
}
const Block& getBlock(int r, int c) const;
void Map::draw() const{
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->mtl.emission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->mtl.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->mtl.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mtl.specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->mtl.shininess);
    glutSolidCube(this->size);
    glPopMatrix();
}
