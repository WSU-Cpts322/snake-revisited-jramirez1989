#include "GameMap.h"

GameMap::GameMap()
{
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);

	height = (yMax / 2) - 20;
	width = (xMax / 2) - 20;

	mapWindow = newwin(40, 40, (yMax / 2) - (40 / 2), (xMax / 2) - (40 / 2));
	initialize();
}

GameMap::GameMap(int h, int w)
{
    height = h;
	width = w;
	mapWindow = newwin(height, width, 0, 0);
	initialize();
}

WINDOW *GameMap::getMapWindow()
{
    return mapWindow;
}
int GameMap::getHeight()
{
	return height;
}
int GameMap::getWidth()
{
	return width;
}
void GameMap::initialize()
{	
    clear();
	refresh();
}

void GameMap::addBorder()
{
	box(mapWindow, 0, 0);
}
void GameMap::clear()
{
	wclear(mapWindow);
	addBorder();
}
void GameMap::refresh()	
{
	wrefresh(mapWindow);
}
