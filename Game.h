/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration of the Game class.
**/

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <vector>

//Class definition of the Game.
class Game{
protected:
	static Game * game; 
	Deck deck;
	vector<Player *> players;
	vector<Player *> tempPlayers;
	vector<string > auto_players;
public:
	Game();
	static Game* instance();
	static void start_game(string const &);
	static void stop_game();
	void add_player(string const &);
	Player* find_player(string const &);
	virtual ~Game();
	virtual int before_turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	virtual size_t size();
	unsigned int pot;
	unsigned int ante;
	unsigned int bet;
	bool if_bet;
	void load_deck();
private:
	Game(Game &);
	void operator= (Game &);

};


#endif

