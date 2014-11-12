/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declaration of cards
**/

#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
using namespace std;

struct Card
{
	enum card_suits {clubs,diamonds,hearts,spades};
	enum card_ranks {two=2,three,four,five,six,seven,eight,nine,ten,jack,queen,king,ace}; 

	//the following declare two member variables
	card_ranks card_ranks_var;
	card_suits card_suits_var;

	string card_suits_var_name;
	string card_ranks_var_name;

	Card (){}; // default constructor
	Card (card_ranks rank, card_suits suit);

	string asString();
};

/*
@brief:less than operator;
*/
bool operator< (const Card &a, const Card &b);

//equivalence operator
bool operator==(const Card &a, const Card &b);

#endif