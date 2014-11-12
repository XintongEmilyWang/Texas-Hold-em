/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration for players.
**/

#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"

using namespace std;

//definition of the player struct.
struct Player{
	string name;
	Hand player_cards;
	unsigned int wins;
	unsigned int losses;
	int chips;
	Player(string);
	int playerBet;
	bool if_fold;
};

ostream & operator<<(ostream &, const Player &);

#endif