//  build_deck.cpp
//  final
//
//  Created by Brooke Bullock on 2014-12-16.
//  Copyright (c) 2014 Brooke Bullock. All rights reserved.

#include "BuildDeck.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "subroutines.h"

using namespace std;

vector <card> BuildDeck (void) {
    vector <card> deck; //reserve space for [112] cards
    
    //basic deck has all 4 base colours and combinations theroff + 2 of each black cards
    //initialize a deck
    card hold;
    
    for (int l=0;l<2;l++) { //puts double deck in the array
        string colour[5] = {"red-", "blue-", "green-", "yellow-", "black-"}; //colours of cards
        string typeA[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "skip_turn", /*"reverse_direction",*/ "pick_up_2"}; //type of cards
        string typeB[2] = {"wild", "pick_up_4/wild"}; //type of cards
        
        //first 52 cards - basic colours
        for (int s=0;s<4;s++) { //loops through colours
            for (int v=0;v<12;v++) {//loops through each card (in each colour)
                hold.colour= colour[s]; //colour is assigned
                hold.type = typeA[v]; //type is assigned
                deck.push_back(hold); //card is put into 'deck'
            }
        }
        //other 4 cards - wild cards
        for (int p=0;p<2;p++) { //2 of each card
            for (int v=0;v<2;v++) {
                hold.colour = colour[4]; //colour is assigned
                hold.type = typeB[v]; //type is assigned
                deck.push_back(hold); //card is put into 'deck'
            }
        }
    }
    return deck;
}
