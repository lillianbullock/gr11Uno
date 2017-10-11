//  main.cpp
//  final
//
//  Created by Brooke Bullock on 2014-12-01.
//  Copyright (c) 2014 Brooke Bullock. All rights reserved.

/*
 user player
 select card in hand to play
 check if card is viable to play
 if not “please choose another card”
 also have 'pick up’ option if no cards to play/ don’t want to play cards
 
 other players
 each have own ‘hand’ of cards
 they play by going through their hand and if card is viable to play it plays that one
 if no cards by end of looking through hand they pick up
 computer chooses wild colour based on colour of most cards in hand?? Or random?
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "subroutines.h" //contains card struct and showcards
#include "BuildDeck.h" //only contains BuildDeck subroutine

using namespace std;

int PickMove(const vector<card> &deck, const vector<card> &table, const vector<card> &user, const string &expected_color) {
    int uin;
    while (true) {
        cout << endl << "The top card on the table is " << table[table.size()-1].colour << table[table.size()-1].type << " " << endl; //shows topcard on table
        
        cout << "Select a Card to play, or press 0 to pick up" << endl;
        showcards(user);
        cin >> uin;
        
        if (uin < 0 || uin > user.size()) {
            cout << endl << "That is not a valid entry, try again" << endl;
            continue;
        }
        
        uin--;
        if (uin == -1) //because one was subtracted from uin => pick up card
            break;
        
        else if (user[uin].colour == "black-")
            break;
        
        else if (table[table.size()-1].colour == user[uin].colour || table[table.size()-1].type == user[uin].type)
            break;
        
        else {
            cout << "That card is an invalid choice, please try again" << endl;
            continue;
        }
    }//end of user play loop
    return uin;
}

int main() {
    cout << "UNO" <<endl;
    
    size_t siz; //unsigned int, removes compilaer warnings :)
    vector <card> deck, table; //deck to be drawn from, and cards in tabe stack
    vector <card> user, comp1, comp2; //user and computer 'hands
    int uin, uin2;
    
    deck = BuildDeck(); //builds double deck
    
    deck = shuffle(deck); //shuffles deck
    
    //show cards
    //showcards(deck);

    for (int l=0;l<7;l++) { //add 7 cards to each hand, adds one to each per loop, loops 7 times
        siz = deck.size()-1;
        
        user.push_back(deck[siz]);
        comp1.push_back(deck[siz-1]);
        comp2.push_back(deck[siz-2]);
        
        for (int c=0;c<3;c++)
           deck.pop_back();
    }
    
    /*
    //shows each hand for testing
    showcards(user);
    cout << endl;
    showcards(comp1);
    cout << endl;
    showcards(comp2);
    */
    
    table.push_back(deck[deck.size()-1]);
    deck.pop_back();
    
    while (table[table.size()-1].colour == "black-") {//prevents black card from being 1st card on stack
        table.push_back(deck[deck.size()-1]);
        deck.pop_back();
    }//showcards (table);
    
    
    string colours[4] = {"red-", "blue-", "green-", "yellow-"};
    string colour_hold_u, colour_hold_c1, colour_hold_c2;
    
    string next_color = deck[deck.size()-1].colour;;
    int pick_up = 0;
    
    vector<vector<card>> users;
    users.push_back(user);
    users.push_back(comp1);
    users.push_back(comp2);
    
    int user_index = 0;
    while (true) {
        user_index = user_index % 3;
        vector<card> user = users[user_index];
        // Start of turn
        for (int i = 0; i < pick_up; i++) {
            cout << "Picking up a card" << endl;
            user.push_back(deck[deck.size()-1]);
            deck.pop_back();
        }
        pick_up = 0;

        if (user_index == 0)
            uin = PickMove(deck, table, user, next_color);
        
        else
            uin = PickMove(deck, table, user, next_color);
            // uin = PickMoveComputer(deck, table, user, next_color);
        
        if (uin == -1) { //because one was subtracted from uin => pick up card
            user.push_back(deck[deck.size()-1]);
            deck.pop_back();
        }
        
        else if (user[uin].colour == "black-") {
            cout << "please select the colour you wish to change to" << endl;
            for (int n=0;n<4;n++)
                cout << n << ": " << colours[n] << endl;
            
            cin >> uin2;
            next_color = colours[uin2];
            
            if (user[uin].type == "pick_up_4/wild")
                pick_up = 4;
            
            table.push_back(user[uin]);
            user.erase(user.begin()+uin);
        }
        
        else{
            cout << user[uin].type << endl;
            showcards(table);
            
            if (user[uin].type == "skip_turn") {
                user_index++;
                cout << endl << "computer 1 cannot play this round" << endl;
            }
            
            else if (user[uin].type == "pick_up_2") { //makes comp 2 pick up 2 cards
                cout << endl << "You will have to pick up" << endl;
                pick_up = 2;
            }

            table.push_back(user[uin]);
            user.erase(user.begin()+uin);
         }
        
        
        if (user.size() == 0) { // if user empties hand of cards, game ends
            cout << "you have emptied your hand and won the game" << endl;
            return 0;
        }

        user_index++;
    } //end of gameplay loop
    return 0;
}



/* basic deck - 56 cards
 red:1 red:2 red:3 red:4 red:5 red:6 red:7 red:8 red:9 red:10 red:skip-turn red:reverse-direction red:pick-up-2
 blue:1 blue:2 blue:3 blue:4 blue:5 blue:6 blue:7 blue:8 blue:9 blue:10 blue:skip-turn blue:reverse-direction blue:pick-up-2
 green:1 green:2 green:3 green:4 green:5 green:6 green:7 green:8 green:9 green:10 green:skip-turn green:reverse-direction green:pick-up-2
 yellow:1 yellow:2 yellow:3 yellow:4 yellow:5 yellow:6 yellow:7 yellow:8 yellow:9 yellow:10 yellow:skip-turn yellow:reverse-direction yellow:pick-up-2
 black:wild black:pick-up-4/wild
 black:wild black:pick-up-4/wild
 Program ended with exit code: 0
*/

/* full double deck - 112 cards
 red:1 red:2 red:3 red:4 red:5 red:6 red:7 red:8 red:9 red:10 red:skip-turn red:reverse-direction red:pick-up-2
 blue:1 blue:2 blue:3 blue:4 blue:5 blue:6 blue:7 blue:8 blue:9 blue:10 blue:skip-turn blue:reverse-direction blue:pick-up-2 
 green:1 green:2 green:3 green:4 green:5 green:6 green:7 green:8 green:9 green:10 green:skip-turn green:reverse-direction green:pick-up-2 
 yellow:1 yellow:2 yellow:3 yellow:4 yellow:5 yellow:6 yellow:7 yellow:8 yellow:9 yellow:10 yellow:skip-turn yellow:reverse-direction yellow:pick-up-2 
 black:wild black:pick-up-4/wild 
 black:wild black:pick-up-4/wild
 red:1 red:2 red:3 red:4 red:5 red:6 red:7 red:8 red:9 red:10 red:skip-turn red:reverse-direction red:pick-up-2 
 blue:1 blue:2 blue:3 blue:4 blue:5 blue:6 blue:7 blue:8 blue:9 blue:10 blue:skip-turn blue:reverse-direction blue:pick-up-2 
 green:1 green:2 green:3 green:4 green:5 green:6 green:7 green:8 green:9 green:10 green:skip-turn green:reverse-direction green:pick-up-2 
 yellow:1 yellow:2 yellow:3 yellow:4 yellow:5 yellow:6 yellow:7 yellow:8 yellow:9 yellow:10 yellow:skip-turn yellow:reverse-direction yellow:pick-up-2 
 black:wild black:pick-up-4/wild 
 black:wild black:pick-up-4/wild
Program ended with exit code: 0*/

//reverse_direction now removed from deck
