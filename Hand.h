/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declarations represent a card player's hand of cards
**/
#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Deck.h"
#include <vector>

class Hand{

private:
	

public:
	vector<Card> hand_vector;
	//returns the card object at that position in the hand
	Card operator[](size_t);
	//remove the card at that position of the vector; throw exception if no card at that position
	void remove_card(size_t);
	Hand(){};
	Hand(const Hand &hand);
	Hand &operator=(const Hand &hand);
	unsigned size() const;
	//equivalence operator
	bool operator==(const Hand &hand) const;
	//the ordering of the first cards that differ determines the ordering of the hand
	bool operator<(const Hand &hand) const;
	string as_string() const;//represent the sequence of cards in the container member variable

	friend ostream &operator<<(ostream &os, const Hand &hand);

	friend void operator<< (Hand &hand, Card & c);

	friend void operator<< (Hand &hand, Deck &deck);
	//help to decide what is the rank of the hand
	friend int rank_helper(const Hand &hand);
	//return true is the first hand ranks higher than the second hand
	friend bool poker_rank(const Hand &handl,const Hand &handr);
	//sorted by highest ranking card
	friend bool no_rank_rank(const Hand &handl,const Hand &handr);
	//sorted by the rank of the pair, then by the highest unpaired card
	friend bool one_pair_rank(const Hand &handl,const Hand &handr);
	//sorted by the rank of the higher pair, then by the rank of the lower pair, then by the 5th card
	friend bool two_pairs_rank(const Hand &handl,const Hand &handr);
	//sorted by the rank of the 3 cards that have the same rank
	friend bool three_of_a_kind_rank(const Hand &handl,const Hand &handr);
	//sorted by the highest rank in each hand
	friend bool straight_rank(const Hand &handl,const Hand &handr);
	//two straight flush hands are sorted by the highest card in each hand
	friend bool flush_rank(const Hand &handl,const Hand &handr);
	//two full house hands are sorted by the rank of the 3 cards that have the same rank and then by the rank of the 2 cards that have the same rank
	friend bool full_house_rank(const Hand &handl,const Hand &handr);
	//sorted by the rank of the 4 cards that have the same rank
	friend bool four_of_a_kind_rank(const Hand &handl,const Hand &handr);
	//sorted by the highest rank card in each hand
	friend bool straight_flush_rank(const Hand &handl,const Hand &handr);
};

//types of hand ranks
enum hand_rank {no_rank=1, one_pair, two_pairs, three_of_a_kind, straight, flush, full_house, four_of_a_kind, straight_flush};

#endif