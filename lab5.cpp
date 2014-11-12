// Lab5.cpp : Defines the entry point for the console application.
/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Create a game and add players into the game, then distribute cards to each game. The game will keep playing unless there is no more player left. 
//Any exception will be caught and user msg will be displayed on the screen.
**/

#include "stdafx.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "lab5.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "TexasHoldEm.h"
#include "Razz.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
using namespace std;


int main(int argc, char* argv[]){

	try{
		if(argc < 3){
			user_message(argv,"Program must be run with the name of a game followed by the names of one or more players");
			return argument_error;
		}
		if(strcmp(argv[1],"FiveCardDraw")!=0 && strcmp(argv[1],"SevenCardStud")!=0 && strcmp(argv[1],"TexasHoldEm")!=0 && strcmp(argv[1],"Razz")!=0){
			user_message(argv,"Only available games are FiveCardDraw, SevenCardStud, TexasHoldEm, and Razz");
			return argument_error;
		}

		if(strcmp(argv[1],"FiveCardDraw")==0){
			FiveCardDraw fcd;
			fcd.start_game(argv[1]);
			fcd.instance();
			for(int i=2; i<argc; i++){
				fcd.add_player(argv[i]);
			}
			while(fcd.size()>0){
				fcd.before_round();
				fcd.round();
				fcd.after_round();
			}
			fcd.stop_game();
		}

		else if(strcmp(argv[1],"SevenCardStud")==0){
			SevenCardStud scs;
			scs.start_game(argv[1]);
			scs.instance();
			for(int i=2;i<argc;i++){
				scs.add_player(argv[i]);
			}
			while(scs.size()>0){
				scs.before_round();
				scs.round();
				scs.after_round();
			}
			scs.stop_game();
		}

		else if(strcmp(argv[1],"TexasHoldEm")==0){
			TexasHoldEm the;
			the.start_game(argv[1]);
			the.instance();
			for(int i=2;i<argc;i++){
				the.add_player(argv[i]);
			}
			while(the.size()>0){
				the.before_round();
				the.round();
				the.after_round();
			}
			the.stop_game();
		}

		else if(strcmp(argv[1],"Razz")==0){
			Razz raz;
			raz.start_game(argv[1]);
			raz.instance();
			for(int i=2;i<argc;i++){
				raz.add_player(argv[i]);
			}
			while(raz.size()>0){
				raz.before_round();
				raz.round();
				raz.after_round();
			}
			raz.stop_game();
		}

		bool replay = true;
		while(replay){
			cout << "Would you like to play another game (yes/no)?" << endl;
			string input;
			getline(cin, input);
			if(input.compare("yes") == 0 || input.compare("Yes") == 0){
				cout << "What game would you like to play?" << endl;
				string input;
				getline(cin, input);
				if(input.compare("FiveCardDraw")!=0 && input.compare("SevenCardStud")!=0 && input.compare("TexasHoldEm")!=0 && input.compare("Razz")!=0){
					cout << "Invalid game type" << endl;
					continue;
				}
				else if(input.compare("FiveCardDraw")==0){
					FiveCardDraw fcd;
					fcd.start_game("FiveCardDraw");
					fcd.instance();
					cout << "How many players?" << endl;
					string input;
					getline(cin, input);
					int newPlayers = stoi(input);
					for(int i=0; i<newPlayers; i++){
						cout << "Enter player name" << endl;
						string input;
						getline(cin, input);
						fcd.add_player(input);
					}
					while(fcd.size()>0){
						fcd.before_round();
						fcd.round();
						fcd.after_round();
					}		
					fcd.stop_game();
				}
				else if(input.compare("SevenCardStud")==0){
					SevenCardStud scs;
					scs.start_game("SevenCardDraw");
					scs.instance();
					cout << "How many players?" << endl;
					string input;
					getline(cin, input);
					int newPlayers = stoi(input);
					for(int i=0; i<newPlayers; i++){
						cout << "Enter player name" << endl;
						string input;
						getline(cin, input);
						scs.add_player(input);
					}
					while(scs.size()>0){
						scs.before_round();
						scs.round();
						scs.after_round();
					}
					scs.stop_game();
				}
				else if(input.compare("TexasHoldEm")==0){
					TexasHoldEm the;
					the.start_game("TexasHoldEm");
					the.instance();
					cout << "How many players?" << endl;
					string input;
					getline(cin, input);
					int newPlayers = stoi(input);
					for(int i=0; i<newPlayers; i++){
						cout << "Enter player name" << endl;
						string input;
						getline(cin, input);
						the.add_player(input);
					}
					while(the.size()>0){
						the.before_round();
						the.round();
						the.after_round();
					}
					the.stop_game();
				}
				else if(input.compare("Razz")==0){
					Razz raz;
					raz.start_game("Razz");
					raz.instance();
					cout << "How many players?" << endl;
					string input;
					getline(cin, input);
					int newPlayers = stoi(input);
					for(int i=0; i<newPlayers; i++){
						cout << "Enter player name" << endl;
						string input;
						getline(cin, input);
						raz.add_player(input);
					}
					while(raz.size()>0){
						raz.before_round();
						raz.round();
						raz.after_round();
					}
					raz.stop_game();
				}
			}
			else{
				replay = false;
				break;
			}
		}
		cout << "Game over" << endl;

	}
	catch(int j){
		string message = "Error #" + j;
		message = message + " caught";
		user_message(argv,(char *)message.c_str());
	}
	catch(...){
		user_message(argv,"Exception Caught, Quitting");
	}
	return program_success;
}

int user_message(char* argv[],char* c) {
	cout<< c <<endl;
	return command_error;
}
