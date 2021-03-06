#include "MainMenu.h"

MainMenu::MainMenu()
{
    x = 0;
    y = 8;
}

void MainMenu::displayE(WINDOW *window, int y, int x)
{
	mvwprintw(window, y++, x, "EEE");
	mvwprintw(window, y++, x, "E");
	mvwprintw(window, y++, x, "EEE");
	mvwprintw(window, y++, x, "E");
	mvwprintw(window, y++, x, "EEE");
}

void MainMenu::displayI(WINDOW *window, int y, int x)
{
	mvwprintw(window, y++, x, "IIII");
	mvwprintw(window, y++, x, " II");
	mvwprintw(window, y++, x, " II");
	mvwprintw(window, y++, x, " II");
	mvwprintw(window, y++, x, "IIII");
}
void MainMenu::displayS(WINDOW *window, int y, int x)
{
	mvwprintw(window, y++, x, "SSS");
	mvwprintw(window, y++, x, "S");
	mvwprintw(window, y++, x, "SSS");
	mvwprintw(window, y++, x, "  S");
	mvwprintw(window, y++, x, "SSS");
}

void MainMenu::displayTitle(WINDOW *window)
{
	int x = 20;
	int y = 2;
	displayS(window, y, x);

	x += 6;
	y = 2;

	mvwprintw(window, y++, x, "NN    N");
	mvwprintw(window, y++, x, "N N   N");
	mvwprintw(window, y++, x, "N   N N");
	mvwprintw(window, y++, x, "N    NN");
	mvwprintw(window, y++, x, "N     N");

	x += 8;
	y = 2;

	mvwprintw(window, y++, x, "      A");
	mvwprintw(window, y++, x, "     A A");
	mvwprintw(window, y++, x, "    AAAAA");
	mvwprintw(window, y++, x, "   A     A");
	mvwprintw(window, y++, x, "  A       A");

	x += 14;
	y = 2;

	mvwprintw(window, y++, x, "K   K    ");
	mvwprintw(window, y++, x, "K  K     ");
	mvwprintw(window, y++, x, "KKK    ");
	mvwprintw(window, y++, x, "K  K   ");
	mvwprintw(window, y++, x, "K   K ");

	x += 8;
	y = 2;

	displayE(window, y, x);

	x = 10;
	y = 8;

	mvwprintw(window, y++, x, "RRR");
	mvwprintw(window, y++, x, "R  R");
	mvwprintw(window, y++, x, "RRR");
	mvwprintw(window, y++, x, "R  R");
	mvwprintw(window, y++, x, "R   R");

	x += 7;
	y = 8;
	displayE(window, y, x);

	x += 5;
	y = 8;
	
	mvwprintw(window, y++, x, "V       V");
	mvwprintw(window, y++, x, " V     V");
	mvwprintw(window, y++, x, "  V   V");
	mvwprintw(window, y++, x, "   V V ");
	mvwprintw(window, y++, x, "    V");

	x += 11;
	y = 8;
	displayI(window, y, x);

	x += 6;
	y = 8;
	displayS(window, y, x);

	x += 5;
	y = 8;
	displayI(window, y, x);

	x += 6;
	y = 8;

	mvwprintw(window, y++, x, "TTTTTT");
	mvwprintw(window, y++, x, "  TT");
	mvwprintw(window, y++, x, "  TT");
	mvwprintw(window, y++, x, "  TT");
	mvwprintw(window, y++, x, "  TT");

	x += 8;
	y = 8;
	displayE(window, y, x);

	x += 6;
	y = 8;

	mvwprintw(window, y++, x, "DDD");
	mvwprintw(window, y++, x, "D  D");
	mvwprintw(window, y++, x, "D   D");
	mvwprintw(window, y++, x, "D  D");
	mvwprintw(window, y++, x, "DDD");
}

void MainMenu::displayHighScores(WINDOW *window, int maxWidth)
{
    ifstream scoreFile;
	int x = 0;
	int y = 12;
	string line = "";

	scoreFile.open("Easy Highscores.txt");
	mvwprintw(window, y + 7, x + 2, "Easy Highscores List");
	while (getline (scoreFile, line))
	{
		mvwprintw(window, y + 8, x + 2, line.c_str());
		getline(scoreFile, line);
		mvwprintw(window, y + 8, x + 6, line.c_str());
		y += 1;
	}
	scoreFile.close();
	line = "";
	y = 12;

	scoreFile.open("Hard Highscores.txt");
	mvwprintw(window, y + 7, maxWidth - 22, "Hard Highscores List");
	while (getline (scoreFile, line))
	{
		mvwprintw(window, y + 8, maxWidth - 22, line.c_str());
		getline(scoreFile, line);
		mvwprintw(window, y + 8, maxWidth - 18, line.c_str());
		y += 1;
	}
	scoreFile.close();
}

void MainMenu::displayMenuControls(WINDOW *window)
{
 	mvwprintw(window, y + 24, x + 16, "Controls: Up and Down arrow keys to move option.");
	mvwprintw(window, y + 25, x + 25, "'Enter' key to select option.");
	mvwprintw(window, y + 26, x + 26, "q to quit the game.");   
}

char MainMenu::displayMenu()
{
    int maxHeight = 41;
	int maxWidth = 81;
	initscr();
	WINDOW * window = newwin(maxHeight, maxWidth, 0, 0);
	clear();
	refresh();
	
	int cursorY = 8;

	int input = ' ';
	noecho();
	keypad(window, true);
	box(window, 0, 0);
	curs_set(0);

	while (true)
	{ 
		displayTitle(window);
		displayHighScores(window, maxWidth);
		displayMenuControls(window);
        clear();
        refresh();
		mvwprintw(window, cursorY + 19, x + 27, "->");
		mvwprintw(window, y + 19, x + 30, "Game Start(Easy)");
		mvwprintw(window, y + 20, x + 30, "Game Start(Hard)");
		input = wgetch(window);

		if ((input == KEY_UP) || (input == KEY_DOWN))
		{
			if (cursorY == 8)
			{
				cursorY = 9;
			}
			else
			{
				cursorY = 8;
			}
		}
		else if (input == '\n')
		{
			if (cursorY == 8)
			{
				return 'E';
			}
			else
			{
				return 'H';
			}
		}
		else if (input == 'q')
		{
			return 'q';
		}
		wclear(window);
		box(window, 0, 0);
		refresh();
	}
}

void MainMenu::processMenu()
{
        while (true)
        {
            char response = displayMenu();
		    clear();
		    endwin();

	        if (response != 'q')
	        {
		        GameEngine game = GameEngine(response);
		        game.startGame();

				if (game.getGameOver() == true)
				{
				    break;
				}
	        }
	        else
	        {
		        break;
	        }
        }
}