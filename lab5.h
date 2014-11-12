/**
Name:Xintong Wang, David Lubin, Zilong Wang
Email:xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
Brief Description:Declarations corresponding to Lab5.cpp
**/

int user_message(char* argv[],char* c);
//avoid hard coding of the return error
enum return_msg{program_success, argument_error, command_error, input_error, hand_size_error, wrong_card_definition, deck_empty_error, load_deck_error, file_open_error, index_out_of_bounds_error, game_already_started, unknown_game, no_game_in_progress, already_playing, not_enough_cards_error};