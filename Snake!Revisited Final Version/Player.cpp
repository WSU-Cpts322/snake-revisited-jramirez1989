#include "Player.h"

Player::Player()
{
	score = 0;
	initials = "BOB";
}
Player::Player(int pScore, string pInitials)
{
	score = pScore;
	initials = pInitials;
}

int Player::getScore()
{
	return score;
}
string Player::getInitials()
{
	return initials;
}

void Player::setScore(int pScore)
{
	score = pScore;
}
void Player::setInitials(string pInitials)
{
	initials = pInitials;
}
