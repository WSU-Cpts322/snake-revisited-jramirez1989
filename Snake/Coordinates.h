#include <iostream>

#ifndef COORDINATES_H
#define COORDINATES_H

using namespace std;

class Coordinates
{
private:
	int xposition;
	int yposition;

public:

	Coordinates();
	Coordinates(int, int);

	int getXposition();
	int getYposition();

	void setXposition(int);
	void setYposition(int);
	bool equals(Coordinates);
};

#endif