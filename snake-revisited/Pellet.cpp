#include "Pellet.h"

Pellet::Pellet()
{
	value = 10;
	location = Coordinates(10, 10);
}
Pellet::Pellet(int number, Coordinates position)
{
	value = number;
	location = position;
}

int Pellet::getValue()
{
	return value;
}
Coordinates Pellet::getLocation()
{
	return location;
}

void Pellet::setValue(int number)
{
	value = number;
}
void Pellet::setLocation(Coordinates position)
{
	location = position;
}