#include <GL/freeglut.h>
#include <random>
#include "idle.h"
#include "Sphere.h"
#include "Map.h"
#include "CollisionHandler.h"

extern PacMan pacman;

extern std::array<Map, STAGE_NUM> maps;

const int FPS = 60;
int sTime = 0;
int eTime = 0;

CollisionHandler colHandler;

Ghost::STATE ghost_state = Ghost::STATE::CHASE;

const float CHASE_SCATTER_TIME = 15000.f;
const float FRIGHTENED_TIME = 15000.f;
const float FRIGHTENED_NORMAL_TIME = 5000.f;
float chase_scatter_sTime;

void updateDirection() {
    /* Implement */
    switch (pacman.getNextDirection()) {
    case Sphere::LEFT:
        if (maps[stage_num].getBlock(pacman.getXIndex() - 1, pacman.getYIndex()).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::RIGHT:
        if (maps[stage_num].getBlock(pacman.getXIndex() + 1, pacman.getYIndex()).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::UP:
        if (maps[stage_num].getBlock(pacman.getXIndex(), pacman.getYIndex() - 1).isPassable()) {
            pacman.updateDirection();
        }
        break;
    case Sphere::DOWN:
        if (maps[stage_num].getBlock(pacman.getXIndex(), pacman.getYIndex() + 1).isPassable()) {
            pacman.updateDirection();
        }
        break;
    default:
        //pacman.updateDirection();
        break;
    }

}

bool checkClear(Map& map)
{
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten())
                return false;
        }
    }
    return true;
}

void createItem(Map& map)   // 맵에서 item이 없다는 전제가 필요
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> whatitem(1, 3);
    int dot_count = 0;
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() == Dot::DOTSIZE::SMALL)
                dot_count++;
        }
    }
    if (!dot_count)  return;
    // 맵에 small dot이 존재할 경우
    std::uniform_int_distribution<> whatdot(1, dot_count);
    Dot::DOTSIZE target_item;
    switch (whatitem(gen))
    {
    case 1:
        target_item = Dot::DOTSIZE::ITEM1;
        break;

    case 2:
        target_item = Dot::DOTSIZE::ITEM2;
        break;

    case 3:
        target_item = Dot::DOTSIZE::ITEM3;
        break;
    }
    int dot_test;
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() == Dot::DOTSIZE::SMALL)
            {
                dot_test = whatdot(gen);
                if (dot_test == 1)
                {
                    map.getDot(col, row).setDotsize(target_item);
                    return;
                }
            }
        }
        if (row == NUM_ROW - 1)
            row = 0;
    }
}

void deleteItem(Map& map)
{
    for (int row = 0; row < NUM_ROW; row++)
    {
        for (int col = 0; col < NUM_COL; col++)
        {
            if (!map.getDot(col, row).getEaten() && map.getDot(col, row).getSize() > 5)
                map.getDot(col, row).setDotsize(Dot::DOTSIZE::SMALL);
        }
    }
}

void idle_main()
{
	// TO DO
	glutPostRedisplay();
}

void idle_ingame()
{
	// TO DO
    float spf = 1000.0f / FPS;
    eTime = glutGet(GLUT_ELAPSED_TIME);

    if (eTime - sTime > spf) {
        bool bNoDir = pacman.getCurrentDirection() == Sphere::DIRECTION::NONE;
        bool bIdxPosUpdated = pacman.isIndexPositionUpdated();
        if (bNoDir || bIdxPosUpdated) {
            updateDirection();
            colHandler(pacman, maps[stage_num]);
            cout << "PM: (" << pacman.getXIndex() << ", " << pacman.getYIndex() << ")" << endl;
        }

        pacman.move();

        sTime = eTime;
        glutPostRedisplay();
    }
    
    if (eTime - chase_scatter_sTime > CHASE_SCATTER_TIME)
    {
        if (ghost_state == Ghost::STATE::CHASE)
        {
            ghost_state = Ghost::STATE::SCATTER;
            // 고스트들의 state를 SCATTER로 변경
        }
        else if (ghost_state == Ghost::STATE::SCATTER)
        {
            ghost_state = Ghost::STATE::CHASE;
            // 고스트들의 state를 CHASE로 변경
        }
    }
}

void idle_end()
{
	// TO DO
}

void idle_savescore()
{
	// TO DO
}

void idle_scoreboard()
{
	// TO DO
}