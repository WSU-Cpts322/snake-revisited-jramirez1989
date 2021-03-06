#include <vector>
#include "Coordinates.h"
#include "Pellet.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
private:
	vector<Coordinates> body;
	char previousDirection;

public:
	Snake();
	vector<Coordinates> getBody();
	char getPreviousDirection();
	void setPreviousDirection(char);
	string moveSnake(char, Pellet, int);
	bool headCollidedWithBody(Coordinates);
	bool headCollidedWithPellet(Pellet);
	void printBodyCoordinates();


};

#endif