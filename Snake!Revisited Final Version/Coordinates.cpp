#include "Coordinates.h"

Coordinates::Coordinates()
{
	xposition = 0;
	yposition = 0;
}
Coordinates::Coordinates(int x, int y)
{
	xposition = x;
	yposition = y;
}

int Coordinates::getXposition()
{
	return xposition;
}
int Coordinates::getYposition()
{
	return yposition;
}

void Coordinates::setXposition(int x)
{
	xposition = x;
}
void Coordinates::setYposition(int y)
{
	yposition = y;
}

bool Coordinates::equals(Coordinates position)
{
	if ((xposition == position.xposition) &&
		(yposition == position.yposition))
	{
		return true;
	}
	else
	{
		return false;
	}

}