#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine()
{
	map = GameMap(41, 81);
	snake = Snake();
	pellet = Pellet();
	poisonPellet = Pellet();
	powerPellet = Pellet();
	currentScore = 0;
	currentLevel = 1;
	pelletsEaten = 0;
	gameSpeed = 1;
	gameDifficulty = 'E';
	gameOver = false;
	powerPelletEaten = false;
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
	powerPelletEaten = false;


	if (difficulty == 'H')
	{
		highscorePlayers = fillHighscorePlayersList('H');
		gameSpeed = 0.05;

		Coordinates position = Coordinates(20, 20);
		poisonPellet = Pellet(-1, position);

		Coordinates position2 = Coordinates(30, 30);
		powerPellet = Pellet(4, position2);

		obstacleList.push_back(Obstacle("Top-left L", 6, 17, 20, 10));
		obstacleList.push_back(Obstacle("Top-right L", 75, 17, 20, 10));
		obstacleList.push_back(Obstacle("Bottom-left L", 6, 33, 20, 10));
		obstacleList.push_back(Obstacle("Bottom-right L", 75, 33, 20, 10));

		obstacleList.push_back(Obstacle("Top-left L", 12, 20, 24, 5));
		obstacleList.push_back(Obstacle("Top-right L", 70, 20, 24, 5));
		obstacleList.push_back(Obstacle("Bottom-left L", 12, 26, 24, 5));
		obstacleList.push_back(Obstacle("Bottom-right L", 70, 26, 24, 5));

		generateNewPellet(pellet);
		generateNewPellet(poisonPellet);
		generateNewPellet(powerPellet);

	}
	else //difficulty == 'E'
	{
		highscorePlayers = fillHighscorePlayersList('E');
		gameSpeed = 0.1;
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

bool GameEngine::headCollidedWithObstacle()
{
	for (int i = 0; i < obstacleList.size(); i++)
	{
		for (int j = 0; j < obstacleList[i].getLocations().size(); j++)
		{
			if (snake.getBody()[0].equals(obstacleList[i].getLocations()[j]))
			{
				return true;
			}
		}
	}
	return false;
}

void GameEngine::generateNewPellet(Pellet currentPellet)
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

		if (currentPellet.getValue() == 1)
		{
			if ((yPosition == poisonPellet.getLocation().getYposition()) &&
			xPosition == poisonPellet.getLocation().getXposition())
			{
				continue;
			}
			if ((yPosition == powerPellet.getLocation().getYposition()) &&
			xPosition == powerPellet.getLocation().getXposition())
			{
				continue;
			}
		}
		else if (currentPellet.getValue() == -1)
		{
			if ((yPosition == pellet.getLocation().getYposition()) &&
			xPosition == pellet.getLocation().getXposition())
			{
				continue;
			}
			if ((yPosition == powerPellet.getLocation().getYposition()) &&
			xPosition == powerPellet.getLocation().getXposition())
			{
				continue;
			}
		}
		else if (currentPellet.getValue() == 4)
		{
			if ((yPosition == pellet.getLocation().getYposition()) &&
			    xPosition == pellet.getLocation().getXposition())
			{
				continue;
			}
			if ((yPosition == poisonPellet.getLocation().getYposition()) &&
			xPosition == poisonPellet.getLocation().getXposition())
			{
				continue;
			}
		}

	    for (unsigned int i = 0; i < snake.getBody().size(); i++)
	    {
			if ((yPosition == snake.getBody()[i].getYposition()) || 
			(xPosition == snake.getBody()[i].getXposition()))
			{
				goodSpot = false;
				break;
			}
	    }

		for (unsigned int i = 0; i < obstacleList.size(); i++)
		{
			for (unsigned int j = 0; j < obstacleList[i].getLocations().size(); j++)
			{
				if ((xPosition == obstacleList[i].getLocations()[j].getXposition()) &&
				(yPosition == obstacleList[i].getLocations()[j].getYposition()))
				{
					goodSpot = false;
					break;
				}
			}
		}
		if (goodSpot == true)
		{
			Coordinates newPosition;
			newPosition.setXposition(xPosition);
			newPosition.setYposition(yPosition);

			if (currentPellet.getValue() == 1)
			{
			    pellet.setLocation(newPosition);
			}
			else if (currentPellet.getValue() == -1)
			{
			    poisonPellet.setLocation(newPosition);
			}
			else if (currentPellet.getValue() == 4)
			{
				powerPellet.setLocation(newPosition);
			}
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
	wgetch(map.getMapWindow());

	if (currentScore > highscorePlayers[4].getScore())
	{
		replaceHighScore();
	}
	map.refresh();

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

void GameEngine::displayPellet(Pellet currentPellet)
{
	wmove(map.getMapWindow(), currentPellet.getLocation().getYposition(), currentPellet.getLocation().getXposition());

	if (currentPellet.getValue() == 1)
	{
	    wprintw(map.getMapWindow(), "@");	
	}
	else if (currentPellet.getValue() == -1)
	{
		wprintw(map.getMapWindow(), "X");
	}
	else if (currentPellet.getValue() == 4)
	{
		wprintw(map.getMapWindow(), "P");
	}
}

void GameEngine::displayObstacle(Obstacle currentObstacle)
{
	for (int i = 0; i < currentObstacle.getLocations().size();i++)
	{
		wmove(map.getMapWindow(), currentObstacle.getLocations()[i].getYposition(),
	        currentObstacle.getLocations()[i].getXposition());

		wprintw(map.getMapWindow(), "#");
	}

}

void GameEngine::replaceHighScore()
{
	int choice = ' ';
	int x = (map.getWidth() / 2.5);
	int y = (map.getHeight() / 2.5);
    char initials[10];

	while (choice != 'y')
	{
	    mvwprintw(map.getMapWindow(), y - 2, x, "NEW HIGH SCORE!");
	    mvwprintw(map.getMapWindow(), y, x, "Enter 3 Initials:");
	    map.refresh();

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

        int cursorY = 18;
        while (true)
	    {
		    mvwprintw(map.getMapWindow(), y - 2, x, "NEW HIGH SCORE!");
			mvwprintw(map.getMapWindow(), y, x, "Enter 3 Initials:");
			mvwprintw(map.getMapWindow(), y, x + 18, initials);
			map.refresh();
            mvwprintw(map.getMapWindow(), y + 2, x, "Submit?    Yes");
	        mvwprintw(map.getMapWindow(), y + 3, x + 11, "No");
	
	        mvwprintw(map.getMapWindow(), cursorY, x + 9, "->");
			mvwprintw(map.getMapWindow(), 32, 4, "Up and down arrow keys to change option, 'enter' key to select an option");

	        choice = wgetch(map.getMapWindow());

		    if ((choice == KEY_UP) || (choice == KEY_DOWN))
		    {
			    if (cursorY == 18)
			    {
				    cursorY = 19;
			    }
			    else
			    {
				    cursorY = 18;
			    }
		    }
		    else if (choice == '\n')
		    {
			    if (cursorY == 18)
			    {
				    choice = 'y';
				    break;
			    }
			    else
			    {
				    choice = 'n';
				    break;
			    }
	    	}
		    map.clear();
		    map.refresh();
	    }
	    map.clear();
	}

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
	int counter = 0;
	const int xBound = map.getWidth() - 2;
	string collisionType = "";

	while(!gameOver)
	{
		curs_set(0);

		displayHeader(xBound);
		displayFooter(xBound);
		displaySnake();
		displayPellet(pellet);

		if (gameDifficulty == 'H')
		{
			displayPellet(poisonPellet);
			displayPellet(powerPellet);

			for (int i = 0; i < obstacleList.size();i++)
			{
				displayObstacle(obstacleList[i]);
			}
		}

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
				collisionType = snake.moveSnake(direction, pellet, counter);
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
			collisionType = snake.moveSnake('U', pellet, counter);
		}
		else if (input == KEY_DOWN)
		{
			collisionType = snake.moveSnake('D', pellet, counter);
		}
		else if (input == KEY_LEFT)
		{
			collisionType = snake.moveSnake('L', pellet, counter);
		}
		else if (input == KEY_RIGHT)
		{
			collisionType = snake.moveSnake('R', pellet, counter);
		}

		if (collisionType == "pellet")
		{
			generateNewPellet(pellet);
			pelletsEaten++;
			currentScore += pellet.getValue();

			if (pelletsEaten % 10 == 0)
			{
				currentLevel++;
			}
		}
		else if (snake.getBody().front().equals(poisonPellet.getLocation()))
		{
			generateNewPellet(poisonPellet);
			pelletsEaten++;
			currentScore += poisonPellet.getValue();

			if (pelletsEaten % 10 == 0)
			{
				currentLevel++;
			}
		}
		else if (snake.getBody().front().equals(powerPellet.getLocation()))
		{
			generateNewPellet(powerPellet);
			pelletsEaten++;
			currentScore += powerPellet.getValue();

			if (pelletsEaten % 10 == 0)
			{
				currentLevel++;
			}
			powerPelletEaten = true;
			counter = 3;
		}
		else if (collisionType == "false")
		{
			powerPelletEaten = false;
		}
		else if (collisionType == "body")
		{
			gameOver = true;
		}
		else if (headCollidedWithBorder())
		{
			gameOver = true;
		}
		else if (headCollidedWithObstacle())
		{
			gameOver = true;
		}
		counter--;
		map.clear();
	}
	if (input != 113)
	{
		displayGameoverScreen();
	}
	endwin();
}
