//  subroutines.cpp
//  final
//
//  Created by Brooke Bullock on 2014-12-04.
//  Copyright (c) 2014 Brooke Bullock. All rights reserved.

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "subroutines.h"

void showcards(vector <card> deck) {
    for (int i=0;i<deck.size();i++)//loops through all cards in deck
        cout << i+1 << ": " <<deck[i].colour << deck[i].type << " " << endl;
   
    cout <<endl;
}

vector <card> shuffle (vector <card> deck1) {
    vector <card> deck2; //deck to shuffle into
    int r; //random value
    
    srand (time(nullptr)); //randomizes seed used for rand function
    
    while (deck1.size() > 0) { //loops through each card in
        r=rand() % deck1.size(); //random number from 0 to one less than the size of deck 1
        deck2.push_back(deck1[r]); //does this remove the card from deck1? //puts random card from deck1 into deck2
        deck1.erase(deck1.begin()+r);
    }
    return deck2; //makes deck2 the new deck
}
