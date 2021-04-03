#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine()
{
	map = GameMap(41, 81);
	snake = Snake();
	pellet = Pellet();
	currentScore = 0.1;
	currentLevel = 1;
	pelletsEaten = 0;
	gameSpeed = 1;
	gameDifficulty = 'E';
	gameOver = false;
	powerPexists = false;
	poisonPexists = false;
	obstaclesExist = false;
}

GameEngine::GameEngine(char difficulty)
{
	initscr();
	refresh();

	currentScore = 0;
	gameOver = false;
	snake = Snake();
	pellet = Pellet();

	gameDifficulty = difficulty;
	currentLevel = 1;
	pelletsEaten = 0;
	map = GameMap(41, 81);

	if (difficulty == 'H')
	{
		highscorePlayers = fillHighscorePlayersList('H');
		gameSpeed = 0.05;
		powerPexists = true;
		poisonPexists = true;
		obstaclesExist = true;

	}
	else //difficulty == 'E'
	{
		highscorePlayers = fillHighscorePlayersList('E');
		gameSpeed = 0.1;
		powerPexists = false;
		poisonPexists = false;
		obstaclesExist = false;
	}
}

vector<Player> GameEngine::fillHighscorePlayersList(char difficulty)
{
	vector<Player> list = vector<Player>(5);
	ifstream scoreFile;
	int counter = 0;
	if (difficulty == 'E')
	{
		scoreFile.open("Easy Highscores.txt");
		string line = "";

		while (getline (scoreFile, line))
		{
			list[counter].setInitials(line);
			getline(scoreFile, line);
			stringstream score(line);
			int s = 0;
			score >> s;
			list[counter].setScore(s);
			counter++;
		}
	}
	else if (difficulty == 'H')
	{
		scoreFile.open("Hard Highscores.txt");
		string line = "";

		while (getline (scoreFile, line))
		{
			list[counter].setInitials(line);
			getline(scoreFile, line);
			stringstream score(line);
			int s = 0;
			score >> s;
			list[counter].setScore(s);
			counter++;

		}
	}
	scoreFile.close();
	return list;
}

int GameEngine::getCurrentScore()
{
	return currentScore;
}
int GameEngine::getCurrentLevel()
{
	return currentLevel;
}
int GameEngine::getPelletsEaten()
{
	return pelletsEaten;
}
double GameEngine::getGameSpeed()
{
	return gameSpeed;
}
char GameEngine::getGameDifficulty()
{
	return gameDifficulty;
}
bool GameEngine::getPowerPexists()
{
	return powerPexists;
}
bool GameEngine::getPoisonPexists()
{
	return poisonPexists;
}
bool GameEngine::getObstaclesExist() 
{
	return obstaclesExist;
}
bool GameEngine::getGameOver()
{
	return gameOver;
}

void GameEngine::setGameOver(bool value)
{
	gameOver = value;
}
void GameEngine::incrementScore(int value)
{
	currentScore += value;
}
void GameEngine::decrementScore(int value)
{
	currentScore -= value;
}

bool GameEngine::headCollidedWithBorder()
{
	const int lowerYBound = map.getHeight() - 4;
	const int upperYBound = 3;
	const int leftXBound = 0;
	const int rightXBound = map.getWidth() - 1;

	int x = snake.getBody()[0].getXposition();
	int y = snake.getBody()[0].getYposition();

	if ((x == leftXBound) || (x == rightXBound))
	{
		return true;
	}
	else if ((y == lowerYBound) || (y == upperYBound))
	{
		return true;
	}
	return false;
}

void GameEngine::generateObstacle()
{

}

void GameEngine::generateNewPellet()
{
	const int lowerYBound = map.getHeight() - 4;
	const int upperYBound = 6;
	const int leftXBound = 1;
	const int rightXBound = map.getWidth() - 2;

	while (true)
	{
	    int yPosition = upperYBound + (rand() % (upperYBound - lowerYBound + 1));
	    int xPosition = leftXBound + (rand() % (rightXBound - leftXBound + 1));
		bool goodSpot = true;

	    for (unsigned int i = 0; i < snake.getBody().size(); i++)
	    {
			if ((yPosition == snake.getBody()[i].getYposition()) || 
			(xPosition == snake.getBody()[i].getXposition()))
			{
				goodSpot = false;
				break;
			}
	    }
		if (goodSpot == true)
		{
			Coordinates newPosition;
			newPosition.setXposition(xPosition);
			newPosition.setYposition(yPosition);
			pellet.setLocation(newPosition);
			return;
		}
	}
}

void GameEngine::displayHeader(int xBound)
{
		mvwprintw(map.getMapWindow(), 1, 5, "Score: ");
		char score[1000];
		sprintf(score, "%d", currentScore);
		mvwprintw(map.getMapWindow(), 1, 12, score);

		mvwprintw(map.getMapWindow(), 1, 30, "High Score: ");
		char highscore[1000];
		sprintf(highscore, "%d", highscorePlayers[0].getScore());
		mvwprintw(map.getMapWindow(), 1, 42, highscore);

		mvwprintw(map.getMapWindow(), 1, 65, "Level:");
		char gameLevel[1000];
		sprintf(gameLevel, "%d", currentLevel);
		mvwprintw(map.getMapWindow(), 1, 71, gameLevel);

		char boundary[xBound];

		for (int i = 0; i < xBound; i++)
		{
			boundary[i] = '-';
		}
		mvwprintw(map.getMapWindow(), 3, 1, boundary);
}

void GameEngine::displayFooter(int xBound)
{
		mvwprintw(map.getMapWindow(), map.getHeight() - 2, 5, "Controls: Movement = arrow keys");
		mvwprintw(map.getMapWindow(), map.getHeight() - 2, 45, "pause = p");
		char highscore[1000];
		mvwprintw(map.getMapWindow(), map.getHeight() - 2, 65, "quit = q");

		char boundary[xBound];

		for (int i = 0; i < xBound; i++)
		{
			boundary[i] = '-';
		}
		mvwprintw(map.getMapWindow(), map.getHeight() - 4, 1, boundary);
}

void GameEngine::displayGameoverScreen()
{
	map.clear();
	map.refresh();
	nodelay(map.getMapWindow(), false);
	mvwprintw(map.getMapWindow(), map.getHeight() / 2.5, map.getWidth() / 2.5, "GAME OVER");
	map.refresh();
	wgetch(map.getMapWindow());
	if (currentScore > highscorePlayers[4].getScore())
	{
		replaceHighScore();
	}

}

void GameEngine::displayPause()
{
	int x = (map.getWidth() / 3) + 5;

	mvwprintw(map.getMapWindow(), map.getHeight() - 3, x, "GAME PAUSED");
	mvwprintw(map.getMapWindow(), 2, x, "GAME PAUSED");
}

void GameEngine::displaySnake()
{
	for(int i = 0; i < snake.getBody().size(); i++)
	{
	    wmove(map.getMapWindow(), snake.getBody()[i].getYposition(), snake.getBody()[i].getXposition());
	    if (i == 0)
	    {
		    wprintw(map.getMapWindow(), "H");
	    }
	    else
	    {
	        wprintw(map.getMapWindow(), "O");
	    }
	}
}

void GameEngine::displayPellet()
{
	wmove(map.getMapWindow(), pellet.getLocation().getYposition(), pellet.getLocation().getXposition());
	wprintw(map.getMapWindow(), "@");	
}

void GameEngine::replaceHighScore()
{
	map.refresh();
	int x = (map.getWidth() / 2.5);
	int y = (map.getHeight() / 2.5);

	mvwprintw(map.getMapWindow(), y, x, "Enter 3 Initials:");
	map.refresh();

	char initials[10];

	char first = wgetch(map.getMapWindow());
	sprintf(initials, "%c", first);
	mvwprintw(map.getMapWindow(), y, x + 18, initials);
	map.refresh();

	char second = wgetch(map.getMapWindow());
	sprintf(initials, "%s%c", initials, second);
	mvwprintw(map.getMapWindow(), y, x + 18, initials);
	map.refresh();

	char third = wgetch(map.getMapWindow());
	sprintf(initials, "%s%c", initials, third);
	mvwprintw(map.getMapWindow(), y, x + 18, initials);
	map.refresh();

	Player user = Player(currentScore, initials);

	for (int i = 0; i < highscorePlayers.size(); i++)
	{
		if (currentScore > highscorePlayers[i].getScore())
		{
			highscorePlayers.insert(highscorePlayers.begin() + i, user);
			highscorePlayers.pop_back();
			writeHighScores();
			break;
		}
	}
}

void GameEngine::writeHighScores()
{
	ofstream scoreList;

	if (gameDifficulty == 'E')
	{
		scoreList.open("Easy Highscores.txt");
	}
	else if (gameDifficulty == 'H')
	{
		scoreList.open("Hard Highscores.txt");
	}

	for (int i = 0; i < highscorePlayers.size();i++)
	{
		scoreList << highscorePlayers[i].getInitials() << endl;
		char score[1000];
		sprintf(score, "%d\n", highscorePlayers[i].getScore());
		scoreList << score;
	}

	scoreList.close();
}

void GameEngine::startGame()
{
	noecho();
	keypad(map.getMapWindow(), true);
	srand(time(NULL));
	nodelay(map.getMapWindow(), true);

	int input;
	const int xBound = map.getWidth() - 2;
	string collisionType = "";

	while(!gameOver)
	{
		curs_set(0);

		displayHeader(xBound);
		displayFooter(xBound);
		displaySnake();
		displayPellet();

		map.refresh();

		double maxTime = gameSpeed;
		double duration;
		clock_t start = clock();

		while (true)
		{
			duration = (clock() - start) / (double) CLOCKS_PER_SEC;
			input = wgetch(map.getMapWindow());
			if ((input != ERR))
			{
				break;
			}
			if (maxTime <= duration)
			{
				char direction = snake.getPreviousDirection();
				collisionType = snake.moveSnake(direction, pellet);
				break;
			}
		}

		if (input == 'q')
		{
			gameOver = true;
		}
		else if (input == 'p')
		{
			displayPause();
			map.refresh();

			while (true)
			{
				input = wgetch(map.getMapWindow());
				if (input == 'p')
				{
					break;
				}
				else if (input == 'q')
				{
					gameOver = true;
					break;
				}

			}
		}
		else if (input == KEY_UP)
		{
			collisionType = snake.moveSnake('U', pellet);
		}
		else if (input == KEY_DOWN)
		{
			collisionType = snake.moveSnake('D', pellet);
		}
		else if (input == KEY_LEFT)
		{
			collisionType = snake.moveSnake('L', pellet);
		}
		else if (input == KEY_RIGHT)
		{
			collisionType = snake.moveSnake('R', pellet);
		}

		if (collisionType == "pellet")
		{
			generateNewPellet();
			pelletsEaten++;
			currentScore += pellet.getValue();

			if (pelletsEaten % 10 == 0)
			{
				currentLevel++;
			}
		}
		else if (collisionType == "body")
		{
			gameOver = true;
		}
		else if (headCollidedWithBorder())
		{
			gameOver = true;
		}
		map.clear();
	}
	if (input != 113)
	{
		displayGameoverScreen();
	}
	endwin();
}
