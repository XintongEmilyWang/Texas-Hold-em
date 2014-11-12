/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Load cards into hands from the deck and other hand related operator and functions
**/

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "lab5.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <exception>

//copy constructor
Hand::Hand(const Hand &hand):hand_vector(hand.hand_vector){}

//returns the card object at that position in the hand
Card Hand::operator[](size_t s){
	if(s >= hand_vector.size()){
		throw index_out_of_bounds_error;
	}
	else{
		return hand_vector[s];
	}
}

//remove the card at that position of the vector; throw exception if no card at that position
void Hand::remove_card(size_t s){
	if(s >= hand_vector.size()){
		throw index_out_of_bounds_error;
	}
	else{
		hand_vector.erase(hand_vector.begin()+s);
	}
}

Hand& Hand::operator=(const Hand &hand){
	if(*this==hand){
	}else{
		hand_vector=hand.hand_vector;
	}
	return *this;
}

unsigned Hand::size() const{
	return hand_vector.size();
}

//equivalence operator
bool Hand::operator==(const Hand &hand) const{

	for(unsigned i=0;i<hand_vector.size();i++){
		if((hand_vector[i].card_ranks_var_name!=hand.hand_vector[i].card_ranks_var_name)|
			(hand_vector[i].card_suits_var_name!=hand.hand_vector[i].card_suits_var_name)){
				return false;
		}
	}
	return true;
}

//the ordering of the first cards that differ determines the ordering of the hand
bool Hand::operator<(const Hand &hand) const{
	int size;

	//select the smaller vector size to compare
	if(hand_vector.size()<hand.hand_vector.size()){
		size=hand_vector.size();	
	}else{
		size=hand.hand_vector.size();
	}

	for (int i=0;i<size;i++){
		if(hand_vector[i]<hand.hand_vector[i]){
			return true;
		}else if(hand.hand_vector[i]<hand_vector[i]){
			return false;
		}else{//if all elements are same, the shorter vector is smaller
			if(hand_vector.size()<hand.hand_vector.size()){
				return true;
			}else{
				return false;
			}
		}
	}

	return false;
}

//represent the sequence of cards in the container member variable
string Hand::as_string() const{
	string str="";
	for (unsigned i=0;i<hand_vector.size();i++){
		str=str+hand_vector[i].card_ranks_var_name+hand_vector[i].card_suits_var_name+" ";
	}
	return str;
}

ostream &operator<<(ostream &os, const Hand &hand){
	os<<hand.as_string()<<endl;
	return os;
}

//remove the first card from the deck to hand container
void operator<< (Hand &hand, Deck &deck){
	if(deck.size()!=0){
		hand.hand_vector.push_back((*deck.get_deck_vector())[0]);
		(deck.get_deck_vector())->erase(deck.get_deck_vector()->begin());
		//sort(hand.hand_vector.begin(),hand.hand_vector.end());
	}else{
		throw deck_empty_error;
	}
}

void operator<< (Hand &hand, Card & c){
	hand.hand_vector.push_back(c);
}