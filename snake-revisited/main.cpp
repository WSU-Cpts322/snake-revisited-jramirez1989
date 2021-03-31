#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Coordinates.h"
#include "GameEngine.h"
#include "GameMap.h"
#include "Snake.h"
#include <fstream>
#include <ncurses.h>

using namespace std;

int main()
{
	GameEngine game = GameEngine('H');
	game.startGame();

	return 0;
}
