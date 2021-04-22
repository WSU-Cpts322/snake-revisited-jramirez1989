#include <ncurses.h>

#ifndef GAMEMAP_H
#define GAMEMAP_H

using namespace std; 

class GameMap
{
private:
	WINDOW *mapWindow;
	int height;
	int width;

public:

    GameMap();
	GameMap(int height, int width);

	WINDOW *getMapWindow();
	int getHeight();
	int getWidth();
	void initialize();
	void addBorder();
	void clear();
	void refresh();
};

#endif