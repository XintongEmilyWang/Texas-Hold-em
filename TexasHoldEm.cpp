/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Constructors and functions for the FiveCardDraw class, which inherits Game.
**/

#include "stdafx.h"
#include "TexasHoldEm.h"
#include "lab5.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define HAND_SIZE 2
#define FULL_DECK_FILE "deck.txt"

using namespace std;

#pragma warning( push )
#pragma warning( disable : 4482)

//the constructor for the FiveCardDraw class, which initializes the Deck.
TexasHoldEm::TexasHoldEm(){
	dealer = 0;
	load_deck();
}

#pragma warning( pop ) 

//takes a reference to a Player and returns an int. The method should print out the player's name and the contents of their hand, then use cout to print out a prompt asking the user which (if any) of their cards to discard
//and then use cin (and possibly a string stream) to obtain a response containing valid size_t values for the positions of the cards to discard from the hand.
int TexasHoldEm::before_turn(){
	if(shared.size()>=1){
		cout << "Community: " << shared[0].asString();
	}
	if(shared.size()>=2){
		cout << " " << shared[1].asString();
	}
	if(shared.size()>=3){
		cout << " " << shared[2].asString();
	}
	if(shared.size()>=4){
		cout << " " << shared[3].asString();
	}
	if(shared.size()==5){
		cout << " " << shared[4].asString();
	}
	cout << endl;
	return program_success;
}

int TexasHoldEm::before_turn(Player & p){
	cout << p.name << ": ** **" << p.player_cards[2].asString();
	if(p.player_cards.size()>=4){
		cout << " " << p.player_cards[3].asString();
	}
	if(p.player_cards.size()>=5){
		cout << " " << p.player_cards[4].asString();
	}
	if(p.player_cards.size()>=6){
		cout << " " << p.player_cards[5].asString();
	}
	cout << endl;
	return program_success;
}

// deal the player's hand as many cards from the main deck as the player had discarded (so that the player again ends up with 5 cards in their hand).
int TexasHoldEm::turn(Player & p){
	if(deck.size() < 1){
		return not_enough_cards_error;
	}
	return program_success;
}

//print out the player's name and the contents of their hand (thus showing the result after their discarded cards were replaced), and return 0 to indicate success.
int TexasHoldEm::after_turn(Player & a){
	return program_success;
}

//helper method for betting, called before and after cards are dealt
void TexasHoldEm::betting_helper(){
	int first=dealer+1;
	if_bet = false;
	bet = 0;
	bool betting = true;
	bool betflag =false;//true for autoplayer

	while(betting){
		for(unsigned n=first; n< players.size(); n ++){
			if(if_bet == false){
				if((*players[n]).playerBet >= (int)bet){
					betting = false;
					continue;
				}
				for(unsigned i=0;i<auto_players.size();i++){
					if((*players[n]).name==auto_players[i]){
						betflag=true;
					}
				}
				if(betflag==false){
					for(unsigned int i=0;i<tempPlayers.size();i++){
						sort(tempPlayers[i]->player_cards.hand_vector.begin(),tempPlayers[i]->player_cards.hand_vector.end());
					}
					cout << (*players[n]).name << ": " << (*tempPlayers[n]).player_cards;
					cout << (*players[n]).name << ", you have " << (*players[n]).chips << " chips. Would you like to bet (b) or check (c)?" << endl;
					string input;
					getline (cin , input);
					if(input.compare("b")==0){
						bool goodBet = false;
						while(goodBet == false){
							cout << "How much would you like to bet?" << endl;
							string input;
							getline(cin, input);
							if(stoi(input) < 0 || stoi(input) > 2 || (int)stoi(input) > (*players[n]).chips){
								cout << "Invalid # of chips. Try again" << endl;
							}
							else{
								bet = stoi(input);
								pot += stoi(input);
								(*players[n]).playerBet = stoi(input);
								(*players[n]).chips -= stoi(input);
								goodBet = true;
								if_bet = true;
							}
						}
					}
					else{
						(*players[n]).playerBet = 0;
						continue;
					}
				}
				else{
					int prob_check=rand()%100;
					if(prob_check<33){
						(*players[n]).playerBet = 0;
						continue;
					}
					else if(prob_check<66){
						bet = 1;
						pot += 1;
						(*players[n]).playerBet = 1;
						(*players[n]).chips -= 1;
						if_bet = true;
					}
					else{
						bet = 2;
						pot += 2;
						(*players[n]).playerBet = 2;
						(*players[n]).chips -= 2;
						if_bet = true;
					}

				}
			}

			else if((*players[n]).if_fold == false){
				if((*players[n]).playerBet >= (int)bet){
					betting = false;
					continue;
				}
				else{
					cout << (*players[n]).name << ": " << (*tempPlayers[n]).player_cards;
					cout << (*players[n]).name << ", you have " << (*players[n]).chips << " chips. Would you like to call (c), raise (r), or fold (f or anything else)?" << endl;
					int b;
					if((*players[n]).playerBet>0){
						b=(*players[n]).playerBet;
					}
					else{
						b=0;
						(*players[n]).playerBet=0;
					}
					cout << "You must bet at least " << bet - b << " chips to remain in the round." << endl;
					string input;
					getline(cin, input);
					if(input.compare("c")==0){
						if((*players[n]).chips < (int)(bet-b)){
							pot += (*players[n]).chips;
							(*players[n]).chips = 0;
							(*players[n]).playerBet = bet;
						}
						else{
							pot +=bet- b;
							(*players[n]).chips -=bet- b;
							(*players[n]).playerBet = bet;
						}
					}
					else if(input.compare("r")==0){
						int b;
						if((*players[n]).playerBet>0){
							b=(*players[n]).playerBet;
						}
						else{
							(*players[n]).playerBet=0;
							b=0;
						}
						bool goodBet = false;
						while(goodBet == false){
							cout << "How much would you like to raise?" << endl;
							string input;
							getline(cin, input);
							if(stoi(input) < 0 || stoi(input) > 2 || (unsigned int)stoi(input) > ((bet - b) + stoi(input)) || (int)stoi(input) > (*players[n]).chips){
								cout << "Invalid # of chips. Try again" << endl;
							}
							else{
								pot += (bet - b) + stoi(input);
								bet += stoi(input);
								(*players[n]).playerBet = bet;
								(*players[n]).chips -= (bet - b);
								goodBet = true;
							}
							if((*players[n]).chips<=0){
								(*players[n]).chips=0;
							}
						}
					}
					else{
						cout << (*players[n]).name << " folded" << endl;
						(*players[n]).if_fold = true;
						int cnt=0;
						for(unsigned int i=0;i<players.size();i++){
							if((*players[i]).if_fold==true){
								cnt++;
							}
						}
						if(cnt==players.size()-1){
							return;
						}
					}
				}
			}
		}

		for(int n=0;n<first;n++){
			if(if_bet == false){
				if((*players[n]).playerBet >= (int)bet){
					betting = false;
					continue;
				}
				for(unsigned i=0;i<auto_players.size();i++){
					if((*players[n]).name==auto_players[i]){
						betflag=true;
					}
				}
				//bot never bets, just checks
				if(betflag==false){
					for(unsigned int i=0;i<tempPlayers.size();i++){
						sort(tempPlayers[i]->player_cards.hand_vector.begin(),tempPlayers[i]->player_cards.hand_vector.end());
					}
					cout << (*players[n]).name << ": " << (*tempPlayers[n]).player_cards;
					cout << (*players[n]).name << ", you have " << (*players[n]).chips << " chips. Would you like to bet (b) or check (c)?" << endl;
					string input;
					getline (cin , input);
					if(input.compare("b")==0){
						bool goodBet = false;
						while(goodBet == false){
							cout << "How much would you like to bet?" << endl;
							string input;
							getline(cin, input);
							if(stoi(input) < 0 || stoi(input) > 2 || (int)stoi(input) > (*players[n]).chips){
								cout << "Invalid # of chips. Try again" << endl;
							}
							else{
								bet = stoi(input);
								pot += stoi(input);
								(*players[n]).playerBet = stoi(input);
								(*players[n]).chips -= stoi(input);
								goodBet = true;
								if_bet = true;
							}
						}
					}
					else{
						(*players[n]).playerBet = 0;
						continue;
					}
				}
				else{
					int prob_check=rand()%100;
					if(prob_check<33){
						(*players[n]).playerBet = 0;
						continue;
					}
					else if(prob_check<66){
						bet = 1;
						pot += 1;
						(*players[n]).playerBet = 1;
						(*players[n]).chips -= 1;
						if_bet = true;
					}
					else{
						bet = 2;
						pot += 2;
						(*players[n]).playerBet = 2;
						(*players[n]).chips -= 2;
						if_bet = true;

					}
				}
			}
			else if((*players[n]).if_fold == false){
				if((*players[n]).playerBet >= (int)bet){
					betting = false;
					continue;
				}
				else{
					int b;
					if((*players[n]).playerBet>0){
						b=(*players[n]).playerBet;
					}
					else{
						(*players[n]).playerBet=0;
						b=0;
					}
					cout << (*players[n]).name << ": " << (*tempPlayers[n]).player_cards;
					cout << (*players[n]).name << ", you have " << (*players[n]).chips << " chips. Would you like to call (c), raise (r), or fold (f or anything else)?" << endl;
					cout << "You must bet at least " << bet - b << " chips to remain in the round." << endl;
					string input;
					getline(cin, input);
					if(input.compare("c")==0){
						if((*players[n]).chips < (int)(bet - b)){
							pot += (*players[n]).chips;
							(*players[n]).chips = 0;
							(*players[n]).playerBet = bet;
						}
						else{
							pot += bet - b;
							(*players[n]).chips -= bet - b;
							(*players[n]).playerBet = bet;
						}
					}
					else if(input.compare("r")==0){

						bool goodBet = false;
						while(goodBet == false){
							cout << "How much would you like to raise?" << endl;
							string input;
							getline(cin, input);
							if(stoi(input) < 0 || stoi(input) > 2 || (unsigned int)stoi(input) > ((bet - b) + stoi(input)) || (int)stoi(input) > (*players[n]).chips){
								cout << "Invalid # of chips. Try again" << endl;
							}
							else{
								pot += (bet - b) + stoi(input);
								bet += stoi(input);
								(*players[n]).playerBet = bet;
								(*players[n]).chips -= (bet - b);
								goodBet = true;
							}
							if((*players[n]).chips<=0){
								(*players[n]).chips=0;
							}
						}
					}
					else{
						cout << (*players[n]).name << " folded" << endl;
						(*players[n]).if_fold = true;
						int cnt=0;
						for(unsigned int i=0;i<players.size();i++){
							if((*players[i]).if_fold==true){
								cnt++;
							}
						}
						if(cnt==players.size()-1){
							return;
						}
					}
				}
			}
		}	
	}
}


//call the main deck member variable's shuffle method and then starting with the player just past the position indicated by the dealer member variable 
//(or, if the player in the last position is the dealer, starting at position 0),
// deal one card at a time from the main deck to each player, continuing to iterate through the players until each player has received five cards.
int TexasHoldEm::before_round(){	
	for(unsigned int i=0;i<players.size();i++){
		Player * tempPlayer(players[i]);
		tempPlayers.push_back(tempPlayer);
	}
	pot = 0;
	ante = 1;
	deck.reseed();
	deck.shuffle();
	int first=dealer+1;
	if(dealer==players.size()-1){
		first=0;
	}

	for(unsigned l=first; l< players.size(); l ++){
		(*players[l]).chips -= ante;
		pot += ante;
		(*players[l]).playerBet = -1;
		(*players[l]).if_fold=false;
	}

	for(int m=0;m<first;m++){
		(*players[m]).chips -= ante;
		pot += ante;
		(*players[m]).playerBet = -1;
		(*players[m]).if_fold=false;
	}


	for(unsigned i=0;i<HAND_SIZE;i++){
		for(unsigned j=first; j< players.size(); j ++){
			if(players[j]->if_fold==false){
				players[j]->player_cards<<deck;
			}
		}
		for(int k=0;k<first;k++){
			if(players[k]->if_fold==false){
				players[k]->player_cards<<deck;
			}
		}
	}
	bool flag=false;

	before_turn();

	for(unsigned j=first; j< players.size(); j ++){

		for(unsigned i=0;i<auto_players.size();i++){
			if((*players[j]).name==auto_players[i]){
				flag=true;

			}

		}
		flag=false;
	}
	for(int k=0;k<first;k++){

		for(unsigned i=0;i<auto_players.size();i++){
			if((*players[k]).name==auto_players[i]){
				flag=true;
			}
		}
		flag=false;
	}

	//first betting
	betting_helper();
	int cnt=0;
	for(unsigned int i=0;i<players.size();i++){
		if((*players[i]).if_fold==true){
			cnt++;
		}
	}
	if(cnt==players.size()-1){
		return program_success;
	}

	//giving the card

	for(int i=0;i<5;i++){
		shared<<deck;
		for(unsigned j=first; j< players.size(); j ++){
			if(players[j]->if_fold==false){
				(*players[j]).playerBet = -1;
				players[j]->player_cards<<shared[i];
			}
		}
		for(int k=0;k<first;k++){
			if(players[k]->if_fold==false){
				(*players[k]).playerBet = -1;
				players[k]->player_cards<<shared[i];
			}
		}

		before_turn();

		for(unsigned j=first; j< players.size(); j ++){

			for(unsigned i=0;i<auto_players.size();i++){
				if((*players[j]).name==auto_players[i]){
					flag=true;
					auto_helper(*players[j]);
				}

			}

			flag=false;
		}
		for(int k=0;k<first;k++){

			for(unsigned i=0;i<auto_players.size();i++){
				if((*players[k]).name==auto_players[i]){
					flag=true;
					auto_helper(*players[k]);
				}
			}
			flag=false;
		}



		//betting after each card is served
		betting_helper();
		int cnt=0;
		for(unsigned int i=0;i<players.size();i++){
			if((*players[i]).if_fold==true){
				cnt++;
			}
		}
		if(cnt==players.size()-1){
			return program_success;
		}
	}


	return program_success;
}


#pragma warning( push )
#pragma warning( disable : 4482)
//helper method to decide which cards to drop for the auto players
void TexasHoldEm::auto_helper(Player & p){
	switch(rank_helper(p.player_cards)){
	case hand_rank::straight_flush:
		return;
	case hand_rank::full_house:
		return;
	case hand_rank::straight:
		return;
	case hand_rank::flush:
		return;
	case hand_rank::four_of_a_kind:
		if(p.player_cards[0]==p.player_cards[1]){
			p.player_cards.remove_card(4);
		}else{
			p.player_cards.remove_card(0);
		}
		p.player_cards<<deck;
		return;
	case hand_rank::three_of_a_kind:
		if(p.player_cards[0]==p.player_cards[2]){
			p.player_cards.remove_card(4);
			p.player_cards.remove_card(3);
		}
		else if(p.player_cards[1]==p.player_cards[3]){
			p.player_cards.remove_card(4);
			p.player_cards.remove_card(0);
		}else{
			p.player_cards.remove_card(1);
			p.player_cards.remove_card(0);
		}
		p.player_cards<<deck;
		p.player_cards<<deck;
		return;
	case hand_rank::one_pair:
		if(p.player_cards[0]==p.player_cards[1]){
			p.player_cards.remove_card(4);
			p.player_cards.remove_card(3);
			p.player_cards.remove_card(2);
		}
		else if(p.player_cards[1]==p.player_cards[2]){
			p.player_cards.remove_card(4);
			p.player_cards.remove_card(3);
			p.player_cards.remove_card(0);
		}else if (p.player_cards[2]==p.player_cards[3]){
			p.player_cards.remove_card(4);
			p.player_cards.remove_card(1);
			p.player_cards.remove_card(0);
		}else{
			p.player_cards.remove_card(2);
			p.player_cards.remove_card(1);
			p.player_cards.remove_card(0);
		}
		p.player_cards<<deck;
		p.player_cards<<deck;
		p.player_cards<<deck;
		return;
	case hand_rank::no_rank:
		if(p.player_cards[4].card_ranks_var==Card::ace){
			p.player_cards.remove_card(3);
			p.player_cards.remove_card(2);
			p.player_cards.remove_card(1);
			p.player_cards.remove_card(0);
		}else{
			p.player_cards.remove_card(2);
			p.player_cards.remove_card(1);
			p.player_cards.remove_card(0);
		}
	default:
		return;
	}
}
#pragma warning( pop ) 

// iterate once more through the players (again starting with the one just past the dealer), and at each player calling their turn method and then their after_turn method. If any player's turn method returns a non-zero value.
// the method should immediately return that non-zero value; otherwise if it completes with no problems the method should return 0 to indicate success.
int TexasHoldEm::round(){
	int first=dealer+1;
	if(dealer==players.size()-1){
		first=0;
	}
	for(unsigned j=first; j< players.size(); j ++){
		int a=turn(*players[j]);
		if(a != program_success){
			return a;
		}
		else{
			after_turn(*players[j]);
		}
	}
	for(int k=0;k<first;k++){
		int a = program_success;
		if((*players[k]).if_fold==false){
			a=turn(*players[k]);
		}
		if(a != program_success){
			return a;
		}
		else{
			after_turn(*players[k]);
		}
	}
	return program_success;
}

//helper method of poker_rank.Check if the players are valid, and then rank them based on their hands with the poker_rank function.
bool poker_rank3(Player *p1, Player *p2){
	if(p1==0 || p2==0){
		return false;
	}
	else{

		Hand h_one=best_hand2(p1);
		Hand h_two=best_hand2(p2);
		return poker_rank(h_one,h_two);

	}
}
Hand best_hand2(Player *a){
	Hand best;
	for(unsigned int i=0;i<5;i++){
		best<<a->player_cards[i];
	}

	for(unsigned int m=0;m<a->player_cards.size();m++){
		for(unsigned int n=m+1;n<a->player_cards.size();n++){
			vector<Card> temp;
			for(unsigned int i=0;i<a->player_cards.size();i++){
				temp.push_back(a->player_cards[i]);
			}
			temp.erase(temp.begin()+n);
			temp.erase(temp.begin()+m);
			Hand hand_temp;

			sort(temp.begin(),temp.end());
			for(unsigned int j=0;j<temp.size();j++){
				hand_temp<<temp[j];
			}

			if(poker_rank(hand_temp,best)){
				best=hand_temp;
			}

		}
	}
	return best;
}


//prints out the stats for each player and then puts the discarded cards back to the deck.
//ask if any player wants to leave. If so, delete the player.
//ask if any player wants to join. If so, initialize the player and add it the game.
int TexasHoldEm::after_round(){
	vector<Player *> *v = new vector<Player *>(tempPlayers);
	bool win_by_fold=false;
	int cnt=0;
	int w=0;
	for(unsigned int i=0;i<players.size();i++){
		if((*players[i]).if_fold==true){
			cnt++;
		}
		else{
			w=i;
		}

	}	
	if(cnt==players.size()-1){
		(*players[w]).wins++;
		(*players[w]).chips+=pot;
		cout<<(*players[w]).name<<" won "<<endl;
		win_by_fold=true;
	}
	else{
		sort(v->begin(),v->end(),poker_rank3);
		(*v)[0]->wins++;
		(*v)[0]->chips+=pot;
		cout<<(*v)[0]->name<<" won "<<endl;
		for(unsigned i=1;i<v->size();i++){
			(*v)[i]->losses++;
		}
	}
	for(unsigned j=0;j<v->size();j++){

		cout<<"Name: "<<(*v)[j]->name<<" Wins: "<<(*v)[j]->wins<<" Losses: "<<(*v)[j]->losses<< " Chips: " << (*v)[j]->chips <<endl;
		if(!win_by_fold){
			sort((*v)[j]->player_cards.hand_vector.begin(),(*v)[j]->player_cards.hand_vector.end());
			cout<<(*v)[j]->player_cards<<endl;
		}
		if((*v)[j]->chips <= 0){
			cout << (*v)[j]->name << ", You have no chips left. Would you like to reset your chips to 20 (type \"reset\") or exit the game (type \"quit\")?" << endl;
			string input;
			getline (cin , input);
			if(input.compare("reset")==0){
				(*v)[j]->chips = 20;
			}
			else{
				string fileName = (*v)[j]->name + ".txt";
				ofstream ofs(fileName);
				ofs << *((*v)[j]);
				ofs.close();
				int q = 0;
				for(unsigned i=0; i<players.size();i++){
					if((*v)[j]->name.compare(players[i]->name)==0){
						q=i;
					}
				}
				delete players[q];
				players.erase(players.begin()+q);
				(*v).erase((*v).begin()+j);
			}
		}
	}
	//add the shared cards to the deck
	for(unsigned k=0;k<shared.size();k++){
		deck.add_card(shared[k]);
	}
	for(unsigned int i=0;i<players.size();i++){
		//remove shared cards from player
		for(int m=(int)players[i]->player_cards.size()-1;m>1;m--){
			players[i]->player_cards.remove_card(m);
		}
		//remove individual cards to deck 
		for(int m=1;m>=0;m--){
			deck.add_card(players[i]->player_cards[m]);
			players[i]->player_cards.remove_card(m);	
		}

	}

	vector<unsigned> temp_auto;

	for(unsigned i=0; i<players.size();i++){
		for(unsigned j=0;j<auto_players.size();j++){
			if((*players[i]).name==auto_players[j]){
				temp_auto.push_back(i);
			}
		}
	}

	//using a function of wins and losses and the chips left to decide if the player is going to leave the game or not.
	//there is only one auto player
	if(temp_auto.size()==1){
		int prob=(int)((((*players[temp_auto[0]]).wins+1)/((*players[temp_auto[0]]).losses+1)+(*players[temp_auto[0]]).chips/(20.0))*50.0);
		if(prob>50){
			string fileName = (*players[temp_auto[0]]).name + ".txt";
			ofstream ofs(fileName);
			ofs << *(players[temp_auto[0]]);
			ofs.close();
			delete players[temp_auto[0]];
			auto_players.erase(auto_players.begin());
			players.erase(players.begin()+temp_auto[0]);

		}
	}
	//assign dynamic probability to the two auto players
	else if(temp_auto.size()==2){
		int prob1=(int)((((*players[temp_auto[0]]).wins+1)/((*players[temp_auto[0]]).losses+1)+(*players[temp_auto[0]]).chips/(20.0))*90.0);
		int prob2=(int)((((*players[temp_auto[1]]).wins+1)/((*players[temp_auto[1]]).losses+1)+(*players[temp_auto[1]]).chips/(20.0))*10.0);

		if(prob2>10){
			string fileName = (*players[temp_auto[1]]).name + ".txt";
			ofstream ofs(fileName);
			ofs << *(players[temp_auto[1]]);
			ofs.close();
			delete players[temp_auto[1]];
			auto_players.erase(auto_players.begin()+1);
			players.erase(players.begin()+temp_auto[1]);
		}
		if(prob1>90){
			string fileName = (*players[temp_auto[0]]).name + ".txt";
			ofstream ofs(fileName);
			ofs << *(players[temp_auto[0]]);
			ofs.close();
			delete players[temp_auto[0]];
			auto_players.erase(auto_players.begin());
			players.erase(players.begin()+temp_auto[0]);
		}
	}


	//more than 2 auto player
	else if(temp_auto.size()>2){
		int prob1=(int)((((*players[temp_auto[0]]).wins+1)/((*players[temp_auto[0]]).losses+1)+(*players[temp_auto[0]]).chips/(20.0))*90.0);
		int prob2=(int)((((*players[temp_auto[temp_auto.size()-1]]).wins+1)/((*players[temp_auto[temp_auto.size()-1]]).losses+1)+(*players[temp_auto[temp_auto.size()-1]]).chips/(20.0))*10.0);

		if(prob2>10){
			string fileName = (*players[temp_auto[temp_auto.size()-1]]).name + ".txt";
			ofstream ofs(fileName);
			ofs << *(players[temp_auto[temp_auto.size()-1]]);
			ofs.close();
			delete players[temp_auto[temp_auto.size()-1]];
			auto_players.erase(auto_players.begin()+auto_players.size()-1);
			players.erase(players.begin()+temp_auto[temp_auto.size()-1]);
		}
		for(unsigned k=temp_auto.size()-2;k>=1;k--){
			int prob3=(int)((((*players[temp_auto[k]]).wins+1)/((*players[temp_auto[k]]).losses+1)+(*players[temp_auto[k]]).chips/(20.0))*50.0);
			if(prob3>50){
				string fileName = (*players[temp_auto[k]]).name + ".txt";
				ofstream ofs(fileName);
				ofs << *(players[temp_auto[k]]);
				ofs.close();
				delete players[temp_auto[k]];
				auto_players.erase(auto_players.begin()+k);
				players.erase(players.begin()+temp_auto[k]);
			}
		}
		if(prob1>90){
			string fileName = (*players[temp_auto[0]]).name + ".txt";
			ofstream ofs(fileName);
			ofs << *(players[temp_auto[0]]);
			ofs.close();
			delete players[temp_auto[0]];
			auto_players.erase(auto_players.begin());
			players.erase(players.begin()+temp_auto[0]);
		}
	}

	bool saidNo = false;
	while(!saidNo){
		cout << "Would anyone like to leave?" << endl;
		string input;
		getline (cin , input);
		string names;
		if(input.compare("no") == 0 || input.compare("No") == 0){
			saidNo = true;
			for(unsigned i=0; i<tempPlayers.size();i++){
				tempPlayers.erase(tempPlayers.begin()+i);
			}
		}
		else{
			stringstream is;
			is << input;
			while(is >> names){
				for(unsigned i=0; i<players.size();i++){
					if(names.compare(players[i]->name)==0){
						string fileName = names + ".txt";
						ofstream ofs(fileName);
						ofs << *(players[i]);
						ofs.close();
						delete players[i];
						players.erase(players.begin()+i);
					}
				}
			}
		}
	}

	bool saidNoJoin = false;
	while(!saidNoJoin){
		cout << "Would anyone like to join?" << endl;
		string input;
		getline (cin , input);
		string names;
		if(input.compare("no") == 0 || input.compare("No") == 0){
			saidNoJoin = true;
		}
		else{
			stringstream is;
			is << input;
			while(is >> names){
				try{
					add_player(names);
				}
				catch(...){
					cout << names << " is already playing" << endl;
				}
			}
		}
	}

	if(dealer == players.size()-1){
		dealer = 0;
	}
	else{
		dealer++;
	}
	tempPlayers.clear();
	return program_success;
}