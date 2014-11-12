/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration a deck of cards
**/

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <string>
#include <vector>

class Deck{
private:
	vector<Card> deck_vector;
public:
	Deck(string deck_file);
	bool load(string file);//reads in valid card and insert card objects
	void reseed();//reseed so that the randomization for each deck object is independent
	void shuffle();
	unsigned size() const;
	vector<Card>* get_deck_vector();
	//default constructor
	Deck();
	void add_card(Card);
	void clear_deck_vector();
	friend ostream & operator<< (ostream &os, const Deck &deck);
};

#endif