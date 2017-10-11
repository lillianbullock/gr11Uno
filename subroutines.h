//
//  subroutines.h
//  final
//
//  Created by Brooke Bullock on 2014-12-04.
//  Copyright (c) 2014 Brooke Bullock. All rights reserved.
//

#ifndef __final__subroutines__
#define __final__subroutines__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct card //makes "card" a type to allow for colour and type of card
{
    string colour;
    string type;
};              

void showcards(vector <card> deck);

vector <card> shuffle (vector <card> deck);

#endif /* defined(__final__subroutines__) */
