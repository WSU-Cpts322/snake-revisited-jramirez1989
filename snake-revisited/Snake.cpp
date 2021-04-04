#include "Snake.h"

Snake::Snake()
{
	Coordinates a = Coordinates(33, 10);
	Coordinates b = Coordinates(32, 10);
	Coordinates c = Coordinates(31, 10);

	body.push_back(a);
	body.push_back(b);
	body.push_back(c);
	previousDirection = 'R';
}

vector<Coordinates> Snake::getBody()
{
	return body;
}	

char Snake::getPreviousDirection()
{
	return previousDirection;
}
void Snake::setPreviousDirection(char direction)
{
	previousDirection = direction;
}
string Snake::moveSnake(char direction, Pellet pellet)
{
	Coordinates newHead = body.front();
	int oldPosition;
	if (direction == 'U')
	{
		if (previousDirection == 'D')
		{
		    oldPosition = newHead.getYposition();
		    newHead.setYposition(oldPosition + 1);
			previousDirection = 'D';
		}
		else
		{
		    oldPosition = newHead.getYposition();
		    newHead.setYposition(oldPosition - 1);
			previousDirection = 'U';
		}
	}
	else if (direction == 'D')
	{		
		if (previousDirection == 'U')
		{
		    oldPosition = newHead.getYposition();
		    newHead.setYposition(oldPosition - 1);
			previousDirection = 'U';
		}
		else
		{
		    int oldPosition = newHead.getYposition();
		    newHead.setYposition(oldPosition + 1);
			previousDirection = 'D';
		}
	}
	else if (direction == 'L')
	{
		if (previousDirection == 'R')
		{
		    oldPosition = newHead.getXposition();
		    newHead.setXposition(oldPosition + 1);
			previousDirection = 'R';
		}
		else
		{
		    oldPosition = newHead.getXposition();
		    newHead.setXposition(oldPosition - 1);
			previousDirection = 'L';
		}
	}
	else if (direction == 'R')
	{
		if (previousDirection == 'L')
		{
		    oldPosition = newHead.getXposition();
		    newHead.setXposition(oldPosition - 1);			
			previousDirection = 'L';
		}
		else
		{
		    oldPosition = newHead.getXposition();
		    newHead.setXposition(oldPosition + 1);
			previousDirection = 'R';
		}
	}
	body.insert(body.begin(), newHead);

    
	if (!(headCollidedWithPellet(pellet.getLocation())))
	{
		body.pop_back();
	}
	else
	{
		return "pellet";
	}
	if (headCollidedWithBody(newHead))
	{
		return "body";
	}
	return "good";
}

void Snake::growBody(Coordinates newHeadPosition)
{

}
bool Snake::headCollidedWithBody(Coordinates headPosition)
{
	for (unsigned int i = 1; i < body.size(); i++)
	{
		if (headPosition.equals(body[i]))
		{
			return true;
		}
	}
	return false;
}

bool Snake::headCollidedWithPellet(Coordinates pelletPosition)
{
	if (pelletPosition.equals(body.front()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::printBodyCoordinates()
{
	for (unsigned int i = 0; i < body.size(); i++)
	{
		cout << i << ": " << body[i].getXposition() << ", " << body[i].getYposition() << endl;
	}
}