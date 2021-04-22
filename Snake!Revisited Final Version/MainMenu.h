#ifndef MAINMENU_H
#define MAINMENU_H

#include "MainMenu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "GameEngine.h"
#include "GameMap.h"
#include "Snake.h"
#include <fstream>
#include <ncurses.h>

class MainMenu
{
private:
   int x;
   int y;

public:
    MainMenu();
    void displayE(WINDOW *, int, int);
    void displayI(WINDOW *, int, int);
    void displayS(WINDOW *, int, int);
    void displayTitle(WINDOW *);
    void displayHighScores(WINDOW *, int);
    void displayMenuControls(WINDOW *);
    char displayMenu();
    void processMenu();
};

#endif
