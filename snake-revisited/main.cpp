#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "GameEngine.h"
#include "MainMenu.h"
#include "GameMap.h"
#include "Snake.h"
#include <fstream>
#include <ncurses.h>

using namespace std;

int main()
{
	MainMenu gameMenu = MainMenu();
	gameMenu.processMenu();

	return 0;
}
