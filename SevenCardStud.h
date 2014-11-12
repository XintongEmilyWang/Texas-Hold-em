/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration of the SevenCardStud class.
**/

#ifndef SEVENCARDSTUD_H
#define SEVENCARDSTUD_H

#include "Game.h"

//forward declaration of the game class.
class Game;

//Class definition of FiveCardDraw.
class SevenCardStud: public Game{
protected:
	size_t dealer;
public:
	SevenCardStud();
	virtual int before_turn(Player &);
	virtual void auto_helper(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	void betting_helper();
	
};

Hand best_hand(Player *a);
bool poker_rank2(Player *p1, Player *p2);

#endif