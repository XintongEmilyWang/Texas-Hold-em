/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description: The main frame for the game, should be overridden by the FiveCardDraw.cpp.
**/

#include "stdafx.h"
#include "Game.h"
#include "lab5.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "TexasHoldEm.h"
#include "Razz.h"
#include <string.h>
#include <iostream>

#define FiveCardDrawType "FiveCardDraw"
#define SevenCardStudType "SevenCardStud"
#define TexasHoldEmType "TexasHoldEm"
#define RazzType "Razz"


Game * Game::game = 0;

//default constructor for game.
Game::Game(){

}

//returns a copy of the static pointer member variable
Game* Game::instance(){
	return game;
}

//If the static pointer member variable is non-zero the method should throw a game_already_started exception (how you define your exceptions is again up to you).
//If the C++ style string parameter does not contain "FiveCardDraw" the method should throw an unknown_game exception. 
//Otherwise the method should use the new operator to dynamically allocate an instance of the FiveCardDraw class (to be described below) and store its address in the static pointer member variable.
void Game::start_game(string const & str){
	if(game!=0){
		throw game_already_started;
	}else if(str.compare(FiveCardDrawType)!=0 && str.compare(SevenCardStudType)!=0 && str.compare(TexasHoldEmType)!=0 && str.compare(RazzType)!=0){
		throw unknown_game;
	}else if(str.compare(FiveCardDrawType)==0){
		game = new FiveCardDraw;
	}else if(str.compare(SevenCardStudType)==0){
		game = new SevenCardStud;
	}else if(str.compare(TexasHoldEmType)==0){
		game = new TexasHoldEm;
	}else if(str.compare(RazzType)==0){
		game = new Razz;
	}
}

//if the static pointer member variable is 0 the method should throw a no_game_in_progress exception.
//Otherwise the method should call the appropriate form of the delete operator on the static pointer member variable, and then set the static pointer member variable to 0.
void Game::stop_game(){
	if(!game){
		throw no_game_in_progress;
	}else{
		delete game;
		game=0;
	}
}

// If there is already a player in the game whose name is the same as the passed C++ style string, the method should throw an already_playing exception. 
//Otherwise the method should use the new operator to dynamically allocate a Player with that name, and then push the object's address back into the game's vector of pointers to players.
void Game::add_player(string const & s){
	if(s.back()=='*'){
		string const temp=s.substr(0,s.length()-1);
		for (unsigned i=0;i<players.size();i++){
			if(players[i]->name.compare(temp)==0){
				throw already_playing;
			}
		}
		players.push_back(new Player(temp));
		auto_players.push_back(temp);
	}else{
		for (unsigned i=0;i<players.size();i++){
			if(players[i]->name.compare(s)==0){
				throw already_playing;
			}
		}
		Player * temp = new Player(s);
		if(temp->chips <=0){
			cout << temp->name << ", You have no chips left. Would you like to reset your chips to 20 (type \"r\") or exit the game (type \"quit\" or anything else)?" << endl;
			string input;
			getline (cin , input);
			if(input.compare("r")==0){
				temp->chips = 20;
			}
		}
		if(temp->chips > 0){
			players.push_back(temp);
		}
	}
}

//takes a reference to a const C++ style string as its only parameter, and either returns a pointer to the matching Player object or returns 0 if there is no player in the game with that name.
Player* Game::find_player(string const & str){
	for (unsigned i=0;i<players.size();i++){
		if(players[i]->name.compare(str)==0){
			return players[i];
		}
	}
	return 0;
}

//destructor for the game class.
Game::~Game(){
	for (unsigned i=0;i<players.size();i++){
		delete players[i];
	}
}

//return the size of the player varaible.
size_t Game::size(){
	return players.size();
}

#pragma warning( push )
#pragma warning( disable : 4482)

//loads the deck
void Game::load_deck(){
	deck.add_card(*(new Card(Card::card_ranks::two,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::three,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::four,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::five,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::six,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::seven,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::eight,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::nine,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::ten,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::jack,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::queen,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::king,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::ace,Card::card_suits::clubs)));
	deck.add_card(*(new Card(Card::card_ranks::two,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::three,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::four,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::five,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::six,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::seven,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::eight,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::nine,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::ten,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::jack,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::queen,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::king,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::ace,Card::card_suits::diamonds)));
	deck.add_card(*(new Card(Card::card_ranks::two,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::three,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::four,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::five,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::six,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::seven,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::eight,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::nine,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::ten,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::jack,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::queen,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::king,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::ace,Card::card_suits::hearts)));
	deck.add_card(*(new Card(Card::card_ranks::two,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::three,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::four,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::five,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::six,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::seven,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::eight,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::nine,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::ten,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::jack,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::queen,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::king,Card::card_suits::spades)));
	deck.add_card(*(new Card(Card::card_ranks::ace,Card::card_suits::spades)));

	vector <Card> * dv = deck.get_deck_vector();
	for(unsigned i=0;i<deck.size();i++){
		if((*dv)[i].card_ranks_var==Card::card_ranks::two){
			(*dv)[i].card_ranks_var_name="2";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::three){
			(*dv)[i].card_ranks_var_name="3";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::four){
			(*dv)[i].card_ranks_var_name="4";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::five){
			(*dv)[i].card_ranks_var_name="5";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::six){
			(*dv)[i].card_ranks_var_name="6";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::seven){
			(*dv)[i].card_ranks_var_name="7";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::eight){
			(*dv)[i].card_ranks_var_name="8";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::nine){
			(*dv)[i].card_ranks_var_name="9";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::ten){
			(*dv)[i].card_ranks_var_name="10";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::jack){
			(*dv)[i].card_ranks_var_name="J";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::queen){
			(*dv)[i].card_ranks_var_name="Q";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::king){
			(*dv)[i].card_ranks_var_name="K";
		}
		else if((*dv)[i].card_ranks_var==Card::card_ranks::ace){
			(*dv)[i].card_ranks_var_name="A";
		}
		if((*dv)[i].card_suits_var==Card::card_suits::clubs){
			(*dv)[i].card_suits_var_name="club";
		}
		else if((*dv)[i].card_suits_var==Card::card_suits::spades){
			(*dv)[i].card_suits_var_name="spades";
		}
		else if((*dv)[i].card_suits_var==Card::card_suits::diamonds){
			(*dv)[i].card_suits_var_name="diamonds";
		}
		else if((*dv)[i].card_suits_var==Card::card_suits::hearts){
			(*dv)[i].card_suits_var_name="hearts";
		}
	}
}

#pragma warning( pop ) 
