#include "Player.h"
#include "Snake.h"
#include "Pellet.h"
#include "Coordinates.h"
#include "GameMap.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class GameEngine
{
private:

	vector<Player> highscorePlayers;
	Snake snake;
	Pellet pellet;
	GameMap map;

	int currentScore;
	int currentLevel;
	int pelletsEaten;
	double gameSpeed;
	char gameDifficulty;

	bool powerPexists;
	bool poisonPexists;
	bool obstaclesExist;
	bool gameOver;

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

	bool getPowerPexists();
	bool getPoisonPexists();
	bool getObstaclesExist();
	bool getGameOver();
	vector<Player> fillHighscorePlayersList(char);

	void setGameOver(bool);
	void incrementScore(int);
	void decrementScore(int);

	bool headCollidedWithBorder();

	void generateObstacle();
	void generateNewPellet();

	void displayHeader(int);	
	void displayFooter(int);
	void displayGameoverScreen();
	void displayPause();
	void displaySnake();
	void displayPellet();

	void replaceHighScore();
	void writeHighScores();

	void startGame();
};

#endif