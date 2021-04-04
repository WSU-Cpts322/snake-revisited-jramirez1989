#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
private:

	int score;
	string initials;

public:

	Player();
	Player(int, string);

	int getScore();
	string getInitials();

	void setScore(int);
	void setInitials(string);

};

#endif