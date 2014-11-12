/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration of the FiveCardDraw class.
**/

#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

#include "Game.h"

//forward declaration of the game class.
class Game;

//Class definition of FiveCardDraw.
class FiveCardDraw: public Game{
protected:
	size_t dealer;
	Deck discardDeck;
public:
	FiveCardDraw();
	void betting_helper();
	virtual int before_turn(Player &);
	virtual void auto_helper(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

bool poker_rank1(Player *p1, Player *p2);

#endif