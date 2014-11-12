Grader: Christopher Schulte
Score: 96/100 + 5 extra credit = 101/100

-2, Program does not allow me to give 4 3 2 as a discard argument.
-2, Pair descriptive messages with your exceptions to describe why the game had to be stopped to the user. 


========================================================================
CSE 332 Lab 5:
Name: Xintong Wang, David Lubin, Zilong Wang
Email: xintong.wang@wustl.edu, lubind@wustl.edu, zilongwang@wustl.edu
========================================================================

Included Files:

Card.h
Declaration of cards
Deck.h
Declaration a deck of cards
FiveCardDraw.h
Declarations for functions of FiveCardDraw
Game.h
Declaration of the Game class
Hand.h
Declarations represent a card player's hand of cards
Player.h
Declaration for players
lab5.h
Declarations corresponding to Lab5.cpp
Card.cpp
Card related operator and functions
Deck.cpp
Load cards onto the deck and define related deck functions
FiveCardDraw.cpp
Constructors and functions for the FiveCardDraw class, which inherits Game
Game.cpp
The main frame for the game, should be overridden by the FiveCardDraw.cpp.
Hand.cpp
Load cards into hands from the deck and other hand related operator and functions
Player.cpp
Constructors and functions for players for the poker game.
Rank.cpp
Compare the poker hand ranking of the two players
lab5.cpp
Create a game and add players into the game, then distribute cards to each game. The game will keep playing unless there is no more player left.
Razz.h
Declarations for functions of Razz
Razz.cpp
Constructors and functions for the Razz class, which inherits Game
SevenCardStud.h
Declarations for functions of SevenCardStud
SevenCardStud.cpp
Constructors and functions for the SevenCardStud class, which inherits Game
TexasHoldEm.h
Declarations for functions of TexasHoldEm
TexasHoldEm.cpp
Constructors and functions for the TexasHoldEm class, which inherits Game

=====================================================================================================================================================================
Compiler Errors and Warnings:
1: A linker error occurred when we attempted to override Game functions within FiveCardDraw without a forward declaration of the Game class.
 We fixed this by adding a forward declaration to the beginning of FiveCardDraw.h
2: As required by the programming guidelines, we supress the extension warnings by using #pragma warning(disable:4482)
=====================================================================================================================================================================
Runtime Errors:
1: We had an index out of bound exception when unsigned int was made negative in one of our for loops.
2: When discarding cards from a player's hand, the program was removing the wrong cards, because the indices for the cards in the players' hands changed as cards were removed.
 We fixed this by reversing the order of the for loop in which cards are discarded
3: We had an isuse in which we were returning cards from a players hand to the deck using an invalid index. We fixed the for loop to use the correct indices
Note: all the errors are solved in the hand-in version
=====================================================================================================================================================================

Autoplayer implementation Protocol:
FiveCardDraw:

Discard Cards
straight flush, full house, straight, or flush: do not discard or receive any cards;
four of a kind or two pair: discard the unmatched card and receive one more card;
three of a kind: discard the two unmatched cards and receive two more cards;
one pair: discard the three unmatched cards and receive three more cards;
no rank: if the hand has an ace, discard the other four cards and receive four more 
cards; otherwise, keep the two highest cards, discard the other three, and receive 
three more cards.

Bet (check/bet; call/raise/fold)
In the first betting phase (players have no cards in hand):
Given the option of check/bet, the autoplayer has 1/3 probability of check,
1/3 probability of betting 1 chip and 1/3 probability of betting 2 chips
Given the option of call/raise/fold, the autoplayer will just call to stay in the 
game to see its cards

In the second betting phase (all players have five cards in hand):
If the autoplayer has his hand higher than the Test_Two_Pair hands as we designed,
then the autoplayer will either raise 1 chip or 2 chips, with each 50% probability;
If the autoplayer has his hand lower than the Test_Two_Pair hands as we designed,
then the autoplayer will just call to stay in the game

Reset 20 chips or Quit:
The autoplayer's chips have 50% probability of being reset to 20; and another 50% probability
of quit the game in the case of running out of chips

Stay/Quit the game
We assign probability to the autoplayer to decide whether stay or leave the game 
according to its wins, losses and chips left following the formula:
(((*autoplayers.wins+1)/(*autoplayers.losses+1)+(*autoplayer.chips/(20.0))*90.0 (or 10 or 50)


Sample output for autoplayers:
H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe FiveCardDraw Emi
ly Mike*
Mike bets 2
Emily:
Emily, you have 39 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike bets 2
Emily: 2club 2diamonds 3hearts 7club 8diamonds
Emily, you have 37 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Emily: 2club 2diamonds 3hearts 7club 8diamonds

Which of your cards will you discard?
1
Mike: 3spades 6spades 9diamonds Qspades Adiamonds

Emily: 2club 3hearts 7club 8diamonds 10spades

Mike won
Name: Mike Wins: 3 Losses: 8 Chips: 15
3spades 6spades 9diamonds Qspades Adiamonds

Name: Emily Wins: 5 Losses: 4 Chips: 35
2club 3hearts 7club 8diamonds 10spades

Would anyone like to leave?
no
Would anyone like to join?
no
Emily:
Emily, you have 34 chips. Would you like to bet (b) or check (c)?
c
Emily: 2club 4diamonds 4spades 7diamonds Kclub
Emily, you have 34 chips. Would you like to bet (b) or check (c)?
c
Emily: 2club 4diamonds 4spades 7diamonds Kclub
Emily, you have 34 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 2club 4diamonds 4spades 7diamonds Kclub
Emily, you have 32 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Emily: 2club 4diamonds 4spades 7diamonds Kclub

Which of your cards will you discard?
2
Emily: 2club 4diamonds 7diamonds Jdiamonds Kclub

Mike: 4hearts 9spades Qspades Khearts Aspades

Mike won
Name: Mike Wins: 4 Losses: 8 Chips: 20
4hearts 9spades Qspades Khearts Aspades

Name: Emily Wins: 5 Losses: 5 Chips: 30
2club 4diamonds 7diamonds Jdiamonds Kclub

Would anyone like to leave?
Emily
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

=============
The game wont continue to be played if all the players left are autoplayers.
=============

Sample output:
H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe FiveCardDraw Emi
ly* Mike*
Mike bets 1
Mike bets 2
Mike: 5club 6club 8club Aclub Adiamonds

Emily: 3diamonds 6hearts 10hearts Jclub Kdiamonds

Mike won
Name: Mike Wins: 5 Losses: 8 Chips: 24
5club 6club 8club Aclub Adiamonds

Name: Emily Wins: 5 Losses: 6 Chips: 26
3diamonds 6hearts 10hearts Jclub Kdiamonds

Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over
=====================================================================================================================================================================
Sample Output for TexasHoldEm:


David: 6hearts 7hearts 9spades Jclub
David, you have 23 chips. Would you like to bet (b) or check (c)?

Emily: 7hearts 8diamonds Jclub Jhearts
Emily, you have 23 chips. Would you like to bet (b) or check (c)?

Mike: 6diamonds 7hearts Jclub Kclub
Mike, you have 17 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6hearts 7hearts 9spades Jclub Ahearts
David, you have 23 chips. Would you like to bet (b) or check (c)?

Emily: 7hearts 8diamonds Jclub Jhearts Ahearts
Emily, you have 23 chips. Would you like to bet (b) or check (c)?

Mike: 6diamonds 7hearts Jclub Kclub Ahearts
Mike, you have 17 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6diamonds 6hearts 7hearts 9spades Jclub Ahearts
David, you have 23 chips. Would you like to bet (b) or check (c)?

Emily: 6diamonds 7hearts 8diamonds Jclub Jhearts Ahearts
Emily, you have 23 chips. Would you like to bet (b) or check (c)?

Mike: 6diamonds 6diamonds 7hearts Jclub Kclub Ahearts
Mike, you have 17 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 5hearts 6diamonds 6hearts 7hearts 9spades Jclub Ahearts
David, you have 23 chips. Would you like to bet (b) or check (c)?

Emily: 5hearts 6diamonds 7hearts 8diamonds Jclub Jhearts Ahearts
Emily, you have 23 chips. Would you like to bet (b) or check (c)?

Mike: 5hearts 6diamonds 6diamonds 7hearts Jclub Kclub Ahearts
Mike, you have 17 chips. Would you like to bet (b) or check (c)?

Emily won
Name: Emily Wins: 2 Losses: 2 Chips: 26
5hearts 6diamonds 7hearts 8diamonds Jclub Jhearts Ahearts

Name: Mike Wins: 0 Losses: 6 Chips: 17
5hearts 6diamonds 6diamonds 7hearts Jclub Kclub Ahearts

Name: David Wins: 2 Losses: 1 Chips: 23
5hearts 6diamonds 6hearts 7hearts 9spades Jclub Ahearts

Would anyone like to leave?

Would anyone like to leave?
no
Would anyone like to join?
no
Community: Jclub  7hearts  Ahearts  6diamonds
Emily: 5hearts Jspades
Emily, you have 25 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Mike: 6diamonds 7club
Mike, you have 16 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
f
Mike folded
David: 6spades 10diamonds
David, you have 22 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
David folded
Emily won
Name: Emily Wins: 3 Losses: 2 Chips: 28
Name: Mike Wins: 0 Losses: 6 Chips: 16
Name: David Wins: 2 Losses: 1 Chips: 22
Would anyone like to leave?
no
Would anyone like to join?
no
Community: Jclub  7hearts  Ahearts  6diamonds
Mike: 2spades Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 5hearts 6diamonds
David, you have 21 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
David folded
Emily: 3spades Ahearts
Emily, you have 27 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
Emily folded
Mike won
Name: Emily Wins: 3 Losses: 2 Chips: 27
Name: Mike Wins: 1 Losses: 6 Chips: 18
Name: David Wins: 2 Losses: 1 Chips: 21
Would anyone like to leave?
no
Would anyone like to join?
no
Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 9hearts
David, you have 20 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Emily: 4spades 5hearts
Emily, you have 26 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Mike: 3club 10spades
Mike, you have 17 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 2 chips to remain in the round.
c
David: 6spades 9hearts
David, you have 19 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
c
Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 9hearts Jclub
David, you have 18 chips. Would you like to bet (b) or check (c)?
c
Emily: 4spades 5hearts Jclub
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 10spades Jclub
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 7hearts 9hearts Jclub
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 7hearts Jclub
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 7hearts 10spades Jclub
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6diamonds 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 6diamonds 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 6diamonds 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 5hearts 6diamonds 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 5hearts 6diamonds 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 5hearts 6diamonds 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

David won
Name: David Wins: 3 Losses: 1 Chips: 27
5hearts 6diamonds 6spades 7hearts 9hearts Jclub Ahearts

Name: Emily Wins: 3 Losses: 3 Chips: 24
4spades 5hearts 5hearts 6diamonds 7hearts Jclub Ahearts

Name: Mike Wins: 1 Losses: 7 Chips: 15
3club 5hearts 6diamonds 7hearts 10spades Jclub Ahearts

Would anyone like to leave?

Would anyone like to leave?
David
Would anyone like to leave?
Mike
Would anyone like to leave?
Emily
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe TexasHoldEm Emil
y Mike David

Mike: 2spades 4club
Mike, you have 14 chips. Would you like to bet (b) or check (c)?

David: 2club 8spades
David, you have 26 chips. Would you like to bet (b) or check (c)?
^C
H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe TexasHoldEm Emil
y Mike David

Mike: 6club Jspades
Mike, you have 14 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 5diamonds 10spades
David, you have 26 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 3hearts 4diamonds
Emily, you have 23 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike: 6club Jspades
Mike, you have 13 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Community: 2club
Mike: 2club 6club Jspades
Mike, you have 12 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 2club 5diamonds 10spades
David, you have 24 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 2club 3hearts 4diamonds
Emily, you have 21 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike: 2club 6club Jspades
Mike, you have 11 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Community: 2club  10hearts
Mike: 2club 6club 10hearts Jspades
Mike, you have 10 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 2club 5diamonds 10hearts 10spades
David, you have 22 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
David folded
Emily: 2club 3hearts 4diamonds 10hearts
Emily, you have 19 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
Emily folded
Mike won
Name: Emily Wins: 3 Losses: 3 Chips: 19
Name: Mike Wins: 2 Losses: 7 Chips: 25
Name: David Wins: 3 Losses: 1 Chips: 22
Would anyone like to leave?
Emily
Would anyone like to leave?
Mike
Would anyone like to leave?
David
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over
===============================================================================================================================================================================
Sample Output for FiveCardDraw:

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe FiveCardDraw Emi
ly Mike Bob
Mike:
Mike, you have 20 chips. Would you like to bet (b) or check (c)?
c
Bob:
Bob, you have 24 chips. Would you like to bet (b) or check (c)?
c
Emily:
Emily, you have 17 chips. Would you like to bet (b) or check (c)?

Would anyone like to join?
no
Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 9hearts
David, you have 20 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Emily: 4spades 5hearts
Emily, you have 26 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Mike: 3club 10spades
Mike, you have 17 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 2 chips to remain in the round.
c
David: 6spades 9hearts
David, you have 19 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
c
Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 9hearts Jclub
David, you have 18 chips. Would you like to bet (b) or check (c)?
c
Emily: 4spades 5hearts Jclub
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 10spades Jclub
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 7hearts 9hearts Jclub
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 7hearts Jclub
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 7hearts 10spades Jclub
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 6diamonds 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 6diamonds 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 6diamonds 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

Community: Jclub  7hearts  Ahearts  6diamonds
David: 5hearts 6diamonds 6spades 7hearts 9hearts Jclub Ahearts
David, you have 18 chips. Would you like to bet (b) or check (c)?

Emily: 4spades 5hearts 5hearts 6diamonds 7hearts Jclub Ahearts
Emily, you have 24 chips. Would you like to bet (b) or check (c)?

Mike: 3club 5hearts 6diamonds 7hearts 10spades Jclub Ahearts
Mike, you have 15 chips. Would you like to bet (b) or check (c)?

David won
Name: David Wins: 3 Losses: 1 Chips: 27
5hearts 6diamonds 6spades 7hearts 9hearts Jclub Ahearts

Name: Emily Wins: 3 Losses: 3 Chips: 24
4spades 5hearts 5hearts 6diamonds 7hearts Jclub Ahearts

Name: Mike Wins: 1 Losses: 7 Chips: 15
3club 5hearts 6diamonds 7hearts 10spades Jclub Ahearts

Would anyone like to leave?

Would anyone like to leave?
David
Would anyone like to leave?
Mike
Would anyone like to leave?
Emily
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe TexasHoldEm Emil
y Mike David

Mike: 2spades 4club
Mike, you have 14 chips. Would you like to bet (b) or check (c)?

David: 2club 8spades
David, you have 26 chips. Would you like to bet (b) or check (c)?
^C
H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe TexasHoldEm Emil
y Mike David

Mike: 6club Jspades
Mike, you have 14 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 5diamonds 10spades
David, you have 26 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 3hearts 4diamonds
Emily, you have 23 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike: 6club Jspades
Mike, you have 13 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Community: 2club
Mike: 2club 6club Jspades
Mike, you have 12 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 2club 5diamonds 10spades
David, you have 24 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 2club 3hearts 4diamonds
Emily, you have 21 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike: 2club 6club Jspades
Mike, you have 11 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Community: 2club  10hearts
Mike: 2club 6club 10hearts Jspades
Mike, you have 10 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
David: 2club 5diamonds 10hearts 10spades
David, you have 22 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
David folded
Emily: 2club 3hearts 4diamonds 10hearts
Emily, you have 19 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
Emily folded
Mike won
Name: Emily Wins: 3 Losses: 3 Chips: 19
Name: Mike Wins: 2 Losses: 7 Chips: 25
Name: David Wins: 3 Losses: 1 Chips: 22
Would anyone like to leave?
Emily
Would anyone like to leave?
Mike
Would anyone like to leave?
David
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe FiveCardDraw Emi
ly Mike Bob*
Mike:
Mike, you have 24 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Bob calls
Emily:
Emily, you have 18 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
c
Mike: 2club 6spades 9club 9diamonds Adiamonds
Mike, you have 23 chips. Would you like to bet (b) or check (c)?
f
Bob checks
Emily: 3spades 4club 6hearts 7diamonds 8diamonds
Emily, you have 17 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
2
Mike: 2club 6spades 9club 9diamonds Adiamonds
Mike, you have 23 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 2 chips to remain in the round.
r
How much would you like to raise?
1
Emily: 3spades 4club 6hearts 7diamonds 8diamonds
Emily, you have 15 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
Emily folded
Mike: 2club 6spades 9club 9diamonds Adiamonds

Which of your cards will you discard?
1
Emily: 3spades 4club 6hearts 7diamonds 8diamonds

Which of your cards will you discard?
1
Mike: 2club 4diamonds 9club 9diamonds Adiamonds

Bob: 5diamonds Jhearts Qclub Qdiamonds Kspades

Emily: 3spades 6hearts 7diamonds 8diamonds

Exception Caught, Quitting

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe FiveCardDraw Emi
ly Mike Bob
Mike:
Mike, you have 24 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Bob:
Bob, you have 19 chips. Would you like to call (c), raise (r), or fold (f or any
thing else)?
You must bet at least 1 chips to remain in the round.
c
Emily:
Emily, you have 18 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
f
Emily folded
Mike: 3hearts 5club 6diamonds 6spades Qdiamonds
Mike, you have 23 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
2
Bob: 2hearts 3club 6club 8spades 10diamonds
Bob, you have 18 chips. Would you like to call (c), raise (r), or fold (f or any
thing else)?
You must bet at least 2 chips to remain in the round.
r
How much would you like to raise?
1
Mike: 3hearts 5club 6diamonds 6spades Qdiamonds
Mike, you have 21 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.

Mike folded
Bob won
Name: Emily Wins: 3 Losses: 3 Chips: 18
Name: Mike Wins: 2 Losses: 7 Chips: 21
Name: Bob Wins: 1 Losses: 0 Chips: 25
Would anyone like to leave?
Mike
Would anyone like to leave?
Bob
Would anyone like to leave?
Emily
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

===============================================================================================================================================================================

Sample Output for SevenCardStud:

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe SevenCardStud Em
ily Mike John
Mike: * * Qhearts
John: * * 9hearts
Emily: * * Jclub
Mike: 3diamonds 9diamonds Qhearts
Mike, you have 20 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
John: Qdiamonds Khearts 9hearts
John, you have 19 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Emily: Aspades Jspades Jclub
Emily, you have 17 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
r
How much would you like to raise?
1
Mike: 3diamonds 9diamonds Qhearts
Mike, you have 19 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
John: Qdiamonds Khearts 9hearts
John, you have 18 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Mike: * * Qhearts  2hearts
John: * * 9hearts  Aclub
Emily: * * Jclub  4diamonds
Mike: 3diamonds 9diamonds Qhearts 2hearts
Mike, you have 18 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
2
John: Qdiamonds Khearts 9hearts Aclub
John, you have 17 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 2 chips to remain in the round.
c
Emily: Aspades Jspades Jclub 4diamonds
Emily, you have 15 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 2 chips to remain in the round.
c
Mike: * * Qhearts  2hearts  Jdiamonds
John: * * 9hearts  Aclub  Kdiamonds
Emily: * * Jclub  4diamonds  Jhearts
Mike: 3diamonds 9diamonds Qhearts 2hearts Jdiamonds
Mike, you have 16 chips. Would you like to bet (b) or check (c)?

John: Qdiamonds Khearts 9hearts Aclub Kdiamonds
John, you have 15 chips. Would you like to bet (b) or check (c)?
c
Emily: Aspades Jspades Jclub 4diamonds Jhearts
Emily, you have 13 chips. Would you like to bet (b) or check (c)?
c
Mike: * * Qhearts  2hearts  Jdiamonds  4hearts
John: * * 9hearts  Aclub  Kdiamonds  8spades
Emily: * * Jclub  4diamonds  Jhearts  Qclub
Mike: 3diamonds 9diamonds Qhearts 2hearts Jdiamonds 4hearts
Mike, you have 16 chips. Would you like to bet (b) or check (c)?
c
John: Qdiamonds Khearts 9hearts Aclub Kdiamonds 8spades
John, you have 15 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Emily: Aspades Jspades Jclub 4diamonds Jhearts Qclub
Emily, you have 13 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
c
Mike: 3diamonds 9diamonds Qhearts 2hearts Jdiamonds 4hearts
Mike, you have 16 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Mike: * * Qhearts  2hearts  Jdiamonds  4hearts *

John: * * 9hearts  Aclub  Kdiamonds  8spades *

Emily: * * Jclub  4diamonds  Jhearts  Qclub *

Mike: 3diamonds 9diamonds Qhearts 2hearts Jdiamonds 4hearts 6diamonds
Mike, you have 15 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
2
John: Qdiamonds Khearts 9hearts Aclub Kdiamonds 8spades 10hearts
John, you have 14 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 2 chips to remain in the round.
r
How much would you like to raise?
1
Emily: Aspades Jspades Jclub 4diamonds Jhearts Qclub 3hearts
Emily, you have 12 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 3 chips to remain in the round.
c
Mike: 3diamonds 9diamonds Qhearts 2hearts Jdiamonds 4hearts 6diamonds
Mike, you have 13 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Emily won
Name: Emily Wins: 4 Losses: 3 Chips: 36
Aspades Jspades Jclub 4diamonds Jhearts Qclub 3hearts

Name: John Wins: 0 Losses: 1 Chips: 11
Qdiamonds Khearts 9hearts Aclub Kdiamonds 8spades 10hearts

Name: Mike Wins: 2 Losses: 8 Chips: 12
3diamonds 9diamonds Qhearts 2hearts Jdiamonds 4hearts 6diamonds

Would anyone like to leave?
Emily
Would anyone like to leave?
Mike
Would anyone like to leave?
John
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over


===============================================================================================================================================================================
Extra Credit:

We implemented the razz class in which the worst hand wins the game.
We have considered all the cases such as straight flush and straight, where they are different the SevenCardStud.

The Sample Output is:


H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>lab5.exe Razz Emily Mike
John
Mike: * * Ahearts
John: * * 9hearts
Emily: * * Qclub
Mike: 5diamonds 2diamonds Ahearts
Mike, you have 11 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
John: 7diamonds 4spades 9hearts
John, you have 10 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
c
Emily: 10diamonds 6club Qclub
Emily, you have 35 chips. Would you like to call (c), raise (r), or fold (f or a
nything else)?
You must bet at least 1 chips to remain in the round.
c
Mike: * * Ahearts  2club
John: * * 9hearts  Adiamonds
Emily: * * Qclub  4diamonds
Mike: 5diamonds 2diamonds Ahearts 2club
Mike, you have 10 chips. Would you like to bet (b) or check (c)?
f
John: 7diamonds 4spades 9hearts Adiamonds
John, you have 9 chips. Would you like to bet (b) or check (c)?
c
Emily: 10diamonds 6club Qclub 4diamonds
Emily, you have 34 chips. Would you like to bet (b) or check (c)?
b
How much would you like to bet?
1
Mike: 5diamonds 2diamonds Ahearts 2club
Mike, you have 10 chips. Would you like to call (c), raise (r), or fold (f or an
ything else)?
You must bet at least 1 chips to remain in the round.
f
Mike folded
John: 7diamonds 4spades 9hearts Adiamonds
John, you have 9 chips. Would you like to call (c), raise (r), or fold (f or any
thing else)?
You must bet at least 1 chips to remain in the round.
f
John folded
Emily won
Name: Emily Wins: 5 Losses: 3 Chips: 40
Name: Mike Wins: 2 Losses: 8 Chips: 10
Name: John Wins: 0 Losses: 1 Chips: 9
Would anyone like to leave?
EMily
Would anyone like to leave?
Emily
Would anyone like to leave?
Mike
Would anyone like to leave?
John
Would anyone like to leave?
no
Would anyone like to join?
no
Would you like to play another game (yes/no)?
no
Game over

H:\My Documents\Visual Studio 2010\Projects\lab5\Debug>