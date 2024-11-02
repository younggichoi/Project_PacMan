//
//  Constants.h
//  PacMan
//
//  Created by 이현우 on 11/3/24.
//

#pragma once

/* OpenGL window constants */
#define WINDOW_X 300
#define WINDOW_Y 300

#define WINDOW_W 640        // window's width
#define WINDOW_H 640        // window's height

#define BOUNDARY_X (WINDOW_W)/2
#define BOUNDARY_Y (WINDOW_H)/2





/* GAME constants */
#define NUM_ROW 9
#define NUM_COL 9

#define BLOCK_SIZE 40
#define MOVE_SPEED 1

// map boundary
#define LEFT_BOUNDARY (-(NUM_COL / 2) * BLOCK_SIZE)
#define RIGHT_BOUNDARY ((NUM_COL / 2) * BLOCK_SIZE)
#define TOP_BOUNDARY ((NUM_COL / 2) * BLOCK_SIZE)
#define BOTTOM_BOUNDARY (-(NUM_COL / 2) * BLOCK_SIZE)
