/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description: Constructors and functions for players for the poker game.
**/

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>

//constructor of the player. It initializes wins loss, the name of the player and its cards for each player.
Player::Player(string s) :wins(0),losses(0),name(s),chips(20),player_cards(){
	ifstream ifs;
	ifs.open(s+".txt");
	if (ifs.is_open ())
	{
		string line;
		string str;
		int i =0;
		while(!(ifs.eof())){			  
			getline(ifs,line);
			istringstream isss(line);
			while(isss>>str){
				if(i == 0){
					name = str;
					i++;
					str = "";
				}
				else if(i == 1){
					wins = (unsigned int)stoi(str);
					i++;
					str = "";
				}
				else if(i == 2){
					losses = (unsigned int)stoi(str);
					i++;
					str = "";
				}
				else if(i==3){
					chips = (unsigned int)stoi(str);
					i++;
					str = "";
				}
			}
		}
	}
}

//overloading insertion operator for the player struct.
ostream & operator<<(ostream & os, const Player & p){
	os << p.name << " " << p.wins << " " << p.losses <<" "<< p.chips<< endl;
	return os;
}