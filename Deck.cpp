/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Load cards onto the deck and define related deck functions
**/
#include "stdafx.h"
#include "Deck.h"
#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "lab5.h"
using namespace std;


Deck::Deck(string deck_file){
	if(load(deck_file)){
		reseed();
	} else{
		throw load_deck_error;	
	}
}

//a default constructor that initializes the deck object to be empty
Deck::Deck() :deck_vector(0){
	
}

//add one card at a time to the deck vector
void Deck::add_card(Card c){
	deck_vector.push_back(c);
}

//reads in valid card and insert card objects
bool Deck::load(string file){
	ifstream ifs;
	ifs.open(file);
	if (ifs.is_open ())
	{
		string line;
		string str;
		cout<<"Start reading and inserting cards!"<<endl;
		while(!(ifs.eof())){			  
			getline(ifs,line);
			istringstream isss(line);
			while(isss>>str){
				Card card_instance;
				if((str.length()==3)||(str.length()==2)){
					switch(str.back()){
						//first, check the card suit defined by the last character
					case 'C': case 'c': card_instance.card_suits_var=Card::clubs;
						card_instance.card_suits_var_name="club";
						break;
					case 'D': case 'd': card_instance.card_suits_var=Card::diamonds;
						card_instance.card_suits_var_name="diamonds";
						break;
					case 'H': case 'h': card_instance.card_suits_var=Card::hearts;
						card_instance.card_suits_var_name="hearts";
						break;
					case 'S': case 's': card_instance.card_suits_var=Card::spades;
						card_instance.card_suits_var_name="spades";
						break;
					default: cout<<"Incorrect card suit, "; 
						throw wrong_card_definition;
					}			
					if (str.length()==3){
						str.pop_back();
						if(str.compare("10")==0){
							card_instance.card_ranks_var=Card::ten;
							card_instance.card_ranks_var_name="10";
						}else {
							cout<<"Incorrect card rank, "; 
							throw wrong_card_definition;
						}
					} else{
						switch(str.front()){
						case 'J': case 'j': card_instance.card_ranks_var=Card::jack;
							card_instance.card_ranks_var_name="J"; 
							break;
						case 'Q': case 'q': card_instance.card_ranks_var=Card::queen;
							card_instance.card_ranks_var_name="Q"; 
							break;
						case 'K': case 'k': card_instance.card_ranks_var=Card::king;
							card_instance.card_ranks_var_name="K";
							break;
						case 'A': case 'a': card_instance.card_ranks_var=Card::ace;
							card_instance.card_ranks_var_name="A";
							break;
						case '2': card_instance.card_ranks_var=Card::two;
							card_instance.card_ranks_var_name="2";
							break;
						case '3': card_instance.card_ranks_var=Card::three;
							card_instance.card_ranks_var_name="3";
							break;
						case '4': card_instance.card_ranks_var=Card::four;
							card_instance.card_ranks_var_name="4";
							break;
						case '5': card_instance.card_ranks_var=Card::five;
							card_instance.card_ranks_var_name="5";
							break;
						case '6': card_instance.card_ranks_var=Card::six;
							card_instance.card_ranks_var_name="6";
							break;
						case '7': card_instance.card_ranks_var=Card::seven;
							card_instance.card_ranks_var_name="7";
							break;
						case '8': card_instance.card_ranks_var=Card::eight;
							card_instance.card_ranks_var_name="8";
							break;
						case '9': card_instance.card_ranks_var=Card::nine;
							card_instance.card_ranks_var_name="9";
							break;
						default: cout<<"Incorrect card rank, "; 
							throw wrong_card_definition;
						}
					}
				}else{
					throw wrong_card_definition;
				}
				//put the card instance into the card_vector
				deck_vector.push_back(card_instance);
			}
		}
	}else{
		cout<<"File open failed!"<<endl; //open the warning if the file open failed
		throw file_open_error; //return 2 to indicate an error
	}
	ifs.close();
	return true;
}



//reseed so that the randomization for each deck object is independent
void Deck::reseed(){
	srand(unsigned (time(0)+rand()%17));
}

void Deck::shuffle(){
	for (int i=0;i<rand();i++){
		random_shuffle(deck_vector.begin(),deck_vector.end());
	}
}

unsigned Deck::size() const{
	return deck_vector.size();
}

ostream & operator<< (ostream &os, const Deck &deck){
	for (unsigned i=0; i<deck.deck_vector.size();i++ ){
		os<<deck.deck_vector.at(i).card_ranks_var_name+deck.deck_vector.at(i).card_suits_var_name<< endl;
	}
	return os;
}

void Deck::clear_deck_vector(){
	deck_vector.clear();
}

vector<Card>* Deck::get_deck_vector()
{
	return &deck_vector;
}