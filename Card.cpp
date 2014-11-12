/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Card related operator and functions
**/

#include "stdafx.h"
#include "Card.h"
#include <string>
#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
using namespace std;

//constructor
Card::Card(card_ranks rank, card_suits suit )
{
	card_ranks_var = rank;
	card_suits_var = suit;
}

string Card::asString(){
	string str="";
	str=str+card_ranks_var_name+card_suits_var_name+" ";
	return str;
}

//less than operator: a card is less than another if its rank is less than the other or rank equals but suit is less than
bool operator< (const Card &a, const Card &b) {
	return (a.card_ranks_var < b.card_ranks_var) || ((a.card_ranks_var==b.card_ranks_var) && (a.card_suits_var < b.card_suits_var)); 
}

//equivalence operator: two cards are equal if they have the same suit and rank
bool operator== (const Card &a, const Card &b) {
	return ((a.card_ranks_var==b.card_ranks_var) && (a.card_suits_var==b.card_suits_var)); 
}