/* 
 * File:   Dealer.cpp
 * Author: Jose Temblador
 * Created on July 28, 2021, 5:51 PM
 */

//#include <iostream>  //I/O Library
#include "Dealer.h"

using namespace std;

Dealer::Dealer() {
    hand=0;
    name="";
}

Dealer::~Dealer() {
        
}

Dealer::Dealer(string a, int b) {
    name=a;
    hand=b;
}

void Dealer::setHand(int num) {
    hand=hand+num;
}