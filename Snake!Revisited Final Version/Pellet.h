#include "Coordinates.h"

#ifndef PELLET_H
#define PELLET_H

class Pellet
{
private:
	int value;
	Coordinates location;

public:
	Pellet();
	Pellet(int, Coordinates);

	int getValue();
	Coordinates getLocation();

	void setValue(int);
	void setLocation(Coordinates);
};

#endif