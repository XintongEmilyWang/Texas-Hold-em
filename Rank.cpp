/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Compare the poker hand ranking of the two players
**/


#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "lab5.h"
#include <iostream>
#include <string>
using namespace std;


	#pragma warning( push )
	#pragma warning( disable : 4482)

//help to decide what is the rank of the hand
int rank_helper(const Hand &hand){
	if (hand.size()!=5){
		throw hand_size_error;
	}
	else{

		vector<int> r;
		vector<int> s;
		vector<Card>::const_iterator i;

		for (i=hand.hand_vector.begin();i<hand.hand_vector.end();i++){  
			Card temp=(Card) (*i); 
			//need to store rank and suit independently to judge the rank
			int rank=(*i).card_ranks_var;
			int suit=(*i).card_suits_var;
			r.push_back(rank);
			s.push_back(suit);
		}

		string rank_message="The rank of the five cards is:";
		//check the suit of cards (already sorted) in hand
		if((s[0]==s[1]) &&s[0]==s[2]&&s[0]==s[3]&&s[0]==s[4]){
			if(((r[4]==(r[0]+4))&&(r[3]==(r[0]+3))&&(r[2]==(r[0]+2))&&(r[1]==(r[0]+1)))||
				(r[0]==2&&r[1]==3&&r[2]==4&&r[3]==5&&r[4]==13)){
					rank_message=rank_message+"Straight flush!";
					return hand_rank::straight_flush;
			}else{
				rank_message=rank_message+"Flush!";
				return hand_rank::flush;
			}
		}else{
			if(((r[4]==(r[0]+4))&&(r[3]==(r[0]+3))&&(r[2]==(r[0]+2))&&(r[1]==(r[0]+1)))||
				(r[0]==2&&r[1]==3&&r[2]==4&&r[3]==5&&r[4]==14)){
					rank_message=rank_message+"Straight!";
					return hand_rank::straight;
			}
		}

		//check the rank of cards (already sorted) in hand
		if(((r[0]<r[1])&&(r[1]==r[2])&&(r[1]==r[3])&&(r[1]==r[4]))||
			((r[0]==r[1])&&(r[0]==r[2])&&(r[0]==r[3])&&(r[0]<r[4]))){
				rank_message=rank_message+"Four of a kind!";
				return hand_rank::four_of_a_kind;
		}else{
			if(((r[0]==r[1])&&(r[0]==r[2])&&(r[2]<r[3])&&(r[3]<r[4]))||((r[0]<r[1])&&(r[1]==r[2])&&(r[1]==r[3])&&(r[3]<r[4]))||
				((r[0]<r[1])&&(r[1]<r[2])&&(r[2]==r[3])&&(r[3]==r[4]))){
					rank_message=rank_message+"Three of a kind!";
					return hand_rank::three_of_a_kind;
			}else{
				if(((r[0]==r[1])&&(r[1]<r[2])&&(r[2]==r[3])&&(r[2]==r[4]))||
					((r[0]==r[1])&&(r[0]==r[2])&&(r[0]<r[3])&&(r[3]==r[4]))){
						rank_message=rank_message+"Full house!";
						return hand_rank::full_house;
				}else{
					if(((r[0]<r[1])&&(r[1]==r[2])&&(r[2]<r[3])&&(r[3]==r[4]))||
						((r[0]==r[1])&&(r[1]<r[2])&&(r[2]==r[3])&&(r[3]<r[4]))||
						((r[0]==r[1])&&(r[1]<r[2])&&(r[2]<r[3])&&(r[3]==r[4]))){
							rank_message=rank_message+"Two pairs!";
							return hand_rank::two_pairs;
					}else{
						if((r[0]==r[1])||(r[1]==r[2])||(r[2]==r[3])||(r[3]==r[4])){
							rank_message=rank_message+"One pair!";
							return hand_rank::one_pair;
						}
					}
				}
			}
		}
		if(rank_message.compare("The rank of the five cards is:")==0){
			rank_message=rank_message+"No rank!";
			return hand_rank::no_rank;
		}
		cout<<rank_message<<endl;
		return 0;
	}
}

//return true is the first hand ranks higher than the second hand
bool poker_rank(const Hand &handl,const Hand &handr){
	if(rank_helper(handl)<rank_helper(handr)){
		return false;
	}else if(rank_helper(handr)<rank_helper(handl)){
		return true;
	}else{//when two hands have the same rank
		if(rank_helper(handl)==hand_rank::no_rank){
			return no_rank_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::one_pair){
			return one_pair_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::two_pairs){
			return two_pairs_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::three_of_a_kind){
			return three_of_a_kind_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::straight){
			return straight_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::flush){
			return flush_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::four_of_a_kind){
			return four_of_a_kind_rank(handl,handr);
		}
		else if(rank_helper(handl)==hand_rank::straight_flush){
			return straight_flush_rank(handl,handr);
		}
	}
	return false;
}

#pragma warning( pop ) 

//sorted by highest ranking card
bool no_rank_rank(const Hand &handl,const Hand &handr){
	for(int i=4;i>=0;i--){
		if(handr.hand_vector[i].card_ranks_var<handl.hand_vector[i].card_ranks_var){
			return true;
			//where we fail
		}else if(handr.hand_vector[i].card_ranks_var==handl.hand_vector[i].card_ranks_var){
			continue;
		}else{
			return false;
		}
	}
	return false;
}

//sorted by the rank of the pair, then by the highest unpaired card
bool one_pair_rank(const Hand &handl,const Hand &handr){
	int pairl, highl, middlel, lowl;
	int pairr, highr, middler, lowr;

	//hand left
	if(handl.hand_vector[0].card_ranks_var==handl.hand_vector[1].card_ranks_var){
		pairl=handl.hand_vector[0].card_ranks_var;
		highl=handl.hand_vector[4].card_ranks_var;
		middlel=handl.hand_vector[3].card_ranks_var;
		lowl=handl.hand_vector[2].card_ranks_var;
	}
	else if(handl.hand_vector[1].card_ranks_var==handl.hand_vector[2].card_ranks_var){
		pairl=handl.hand_vector[1].card_ranks_var;
		highl=handl.hand_vector[4].card_ranks_var;
		middlel=handl.hand_vector[3].card_ranks_var;
		lowl=handl.hand_vector[0].card_ranks_var;
	}
	else if(handl.hand_vector[2].card_ranks_var==handl.hand_vector[3].card_ranks_var){
		pairl=handl.hand_vector[2].card_ranks_var;
		highl=handl.hand_vector[4].card_ranks_var;
		middlel=handl.hand_vector[1].card_ranks_var;
		lowl=handl.hand_vector[0].card_ranks_var;
	}
	else if(handl.hand_vector[3].card_ranks_var==handl.hand_vector[4].card_ranks_var){
		pairl=handl.hand_vector[3].card_ranks_var;
		highl=handl.hand_vector[2].card_ranks_var;
		middlel=handl.hand_vector[1].card_ranks_var;
		lowl=handl.hand_vector[0].card_ranks_var;
	}

	//hand right
	if(handr.hand_vector[0].card_ranks_var==handr.hand_vector[1].card_ranks_var){
		pairr=handr.hand_vector[0].card_ranks_var;
		highr=handr.hand_vector[4].card_ranks_var;
		middler=handr.hand_vector[3].card_ranks_var;
		lowr=handr.hand_vector[2].card_ranks_var;
	}
	else if(handr.hand_vector[1].card_ranks_var==handr.hand_vector[2].card_ranks_var){
		pairr=handr.hand_vector[1].card_ranks_var;
		highr=handr.hand_vector[4].card_ranks_var;
		middler=handr.hand_vector[3].card_ranks_var;
		lowr=handr.hand_vector[0].card_ranks_var;
	}
	else if(handr.hand_vector[2].card_ranks_var==handr.hand_vector[3].card_ranks_var){
		pairr=handr.hand_vector[2].card_ranks_var;
		highr=handr.hand_vector[4].card_ranks_var;
		middler=handr.hand_vector[1].card_ranks_var;
		lowr=handr.hand_vector[0].card_ranks_var;
	}
	else if(handr.hand_vector[3].card_ranks_var==handr.hand_vector[4].card_ranks_var){
		pairr=handr.hand_vector[3].card_ranks_var;
		highr=handr.hand_vector[2].card_ranks_var;
		middler=handr.hand_vector[1].card_ranks_var;
		lowr=handr.hand_vector[0].card_ranks_var;
	}

	if(pairr<pairl){
		return true;
	}else if(pairl<pairr){
		return false;
	}else{
		if(highr<highl){
			return true;
		}else if(highl<highr){
			return false;
		}else{
			if(middler<middlel){
				return true;
			}else if(middlel<middler){
				return false;
			}else{
				if(lowr<lowl){
					return true;
				}else{
					return false;
				}
			}
		}
	}
}

//sorted by the rank of the higher pair, then by the rank of the lower pair, then by the 5th card
bool two_pairs_rank(const Hand &handl,const Hand &handr){
	int hpairl,lpairl,singlel,hpairr,lpairr,singler;

	if(handl.hand_vector[0].card_ranks_var==handl.hand_vector[1].card_ranks_var){
		lpairl=handl.hand_vector[0].card_ranks_var;
		hpairl=handl.hand_vector[3].card_ranks_var;
		if(handl.hand_vector[2].card_ranks_var==handl.hand_vector[3].card_ranks_var){
			singlel=handl.hand_vector[4].card_ranks_var;
		}else{
			singlel=handl.hand_vector[2].card_ranks_var;
		}
	}else{
		lpairl=handl.hand_vector[1].card_ranks_var;
		hpairl=handl.hand_vector[3].card_ranks_var;
		singlel=handl.hand_vector[0].card_ranks_var;
	}

	if(handr.hand_vector[0].card_ranks_var==handr.hand_vector[1].card_ranks_var){
		lpairr=handr.hand_vector[0].card_ranks_var;
		hpairr=handr.hand_vector[3].card_ranks_var;
		if(handr.hand_vector[2].card_ranks_var==handr.hand_vector[3].card_ranks_var){
			singler=handr.hand_vector[4].card_ranks_var;
		}else{
			singler=handr.hand_vector[2].card_ranks_var;
		}
	}else{
		lpairr=handr.hand_vector[1].card_ranks_var;
		hpairr=handr.hand_vector[3].card_ranks_var;
		singler=handr.hand_vector[0].card_ranks_var;
	}

	if(hpairr<hpairl){
		return true;
	}else if(hpairl<hpairr){
		return false;
	}else{
		if(lpairr<lpairl){
			return true;
		}else if(lpairl<lpairr){
			return false;
		}else{
			if(singler<singlel){
				return true;
			}else {
				return false;
			}
		}
	}
}

//sorted by the rank of the 3 cards that have the same rank
bool three_of_a_kind_rank(const Hand &handl,const Hand &handr){
	int kindl, kindr;
	if(handl.hand_vector[0].card_ranks_var==handl.hand_vector[2].card_ranks_var){
		kindl=handl.hand_vector[0].card_ranks_var;
	}else if(handl.hand_vector[1].card_ranks_var==handl.hand_vector[3].card_ranks_var){
		kindl=handl.hand_vector[1].card_ranks_var;
	}else{
		kindl=handl.hand_vector[4].card_ranks_var;
	}

	if(handr.hand_vector[0].card_ranks_var==handr.hand_vector[2].card_ranks_var){
		kindr=handr.hand_vector[0].card_ranks_var;
	}else if(handr.hand_vector[1].card_ranks_var==handr.hand_vector[3].card_ranks_var){
		kindr=handr.hand_vector[1].card_ranks_var;
	}else{
		kindr=handr.hand_vector[4].card_ranks_var;
	}

	if(kindr<kindl){
		return true;
	}else{
		return false;
	}

}

//sorted by the highest rank in each hand
bool straight_rank(const Hand &handl,const Hand &handr){
	if(handr.hand_vector[4].card_ranks_var<handl.hand_vector[4].card_ranks_var){
		return true;
	}else{
		return false;
	}
}

//two straight flush hands are sorted by the highest card in each hand
bool flush_rank(const Hand &handl,const Hand &handr){
	for (int i=4; i>=0; i--){
		if(handr.hand_vector[i].card_ranks_var<handl.hand_vector[i].card_ranks_var){
			return true;
		}else if(handl.hand_vector[i].card_ranks_var<handr.hand_vector[i].card_ranks_var){
			return false;
		}
	}

	return false;
}

//two full house hands are sorted by the rank of the 3 cards that have the same rank and then by the rank of the 2 cards that have the same rank
bool full_house_rank(const Hand &handl,const Hand &handr){
	int fhl,fhr;

	if(handl.hand_vector[0].card_ranks_var==handl.hand_vector[2].card_ranks_var){
		fhl=handl.hand_vector[0].card_ranks_var;
	}else{
		fhl=handl.hand_vector[2].card_ranks_var;
	}

	if(handr.hand_vector[0].card_ranks_var==handr.hand_vector[2].card_ranks_var){
		fhr=handr.hand_vector[0].card_ranks_var;
	}else{
		fhr=handr.hand_vector[2].card_ranks_var;
	}

	if(fhr<fhl){
		return true;
	}else{
		return false;
	}
}

//sorted by the rank of the 4 cards that have the same rank
bool four_of_a_kind_rank(const Hand &handl,const Hand &handr){
	int fkl, fkr;
	if(handl.hand_vector[0].card_ranks_var==handl.hand_vector[3].card_ranks_var){
		fkl=handl.hand_vector[0].card_ranks_var;
	}else{
		fkl=handl.hand_vector[1].card_ranks_var;
	}

	if(handr.hand_vector[0].card_ranks_var==handr.hand_vector[3].card_ranks_var){
		fkr=handr.hand_vector[0].card_ranks_var;
	}else{
		fkr=handr.hand_vector[1].card_ranks_var;
	}

	if(fkr<fkl){
		return true;
	}else{
		return false;
	}
}

//sorted by the highest rank card in each hand
bool straight_flush_rank(const Hand &handl,const Hand &handr){
	if(handr.hand_vector[0].card_ranks_var<handl.hand_vector[0].card_ranks_var){
		return true;
	}else{
		return false;
	}
}



