#include "Coordinates.h"
#include "Pellet.h"
#include "Snake.h"
#include "GameMap.h"
#include <vector>
#include <time.h>
#include <stdlib.h>

#ifndef OBSTACLE_H
#define OBSTACLE_H

using namespace std;

class Obstacle
{
    private:
    vector<Coordinates> locations;

    public:
    Obstacle();
    Obstacle(string, int, int, int, int);
    vector<Coordinates> getLocations();
};

#endif