#include "Player.h"
#include "Snake.h"
#include "Pellet.h"
#include "Coordinates.h"
#include "GameMap.h"
#include "Obstacle.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine
{
private:

	vector<Player> highscorePlayers;
	Snake snake;
	Pellet pellet;
	Pellet poisonPellet;
	Pellet powerPellet;
	vector<Obstacle> obstacleList;
	GameMap map;

	int currentScore;
	int currentLevel;
	int pelletsEaten;
	double gameSpeed;
	char gameDifficulty;
	bool gameOver;
	bool powerPelletEaten;

public:
	GameEngine();
	GameEngine(char);

	vector<Player> getHighscorePlayers();
	Snake getSnake();
	GameMap getMap();

	int getCurrentScore();
	int getCurrentLevel();
	int getPelletsEaten();
	double getGameSpeed();
	char getGameDifficulty();

	bool getGameOver();
	vector<Player> fillHighscorePlayersList(char);

	void setGameOver(bool);
	void incrementScore(int);
	void decrementScore(int);

	bool headCollidedWithBorder();
	bool headCollidedWithObstacle();

	void generateNewPellet(Pellet);

	void displayHeader(int);	
	void displayFooter(int);
	void displayGameoverScreen();
	void displayPause();
	void displaySnake();
	void displayPellet(Pellet);
	void displayObstacle(Obstacle);

	void replaceHighScore();
	void writeHighScores();

	void startGame();
};

#endif