/* 
 * File:   Dealer.h
 * Author: Jose Temblador
 *
 * Created on July 28, 2021, 5:50 PM
 */
#include <string>
using namespace std;


#ifndef DEALER_H
#define DEALER_H

class Dealer {
    private:
        int hand;       //The dealer's hand
        string name;    //simply containing "The Dealer"
    public:
        Dealer();
        ~Dealer();
        Dealer(string, int); 
        void setHand(int);   //adds cards to the dealers hand
        int getHand() {return hand;}    //returns the dealers hand
        string getName() {return name;} //returns the dealer's name
};

#endif /* DEALER_H */

