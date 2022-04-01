/* 
 * File:   Cards.h
 * Author: mac
 *
 * Created on July 29, 2021, 12:53 AM
 */

#ifndef CARDS_H
#define CARDS_H
using namespace std;

class CardInfo {
private:
    int cardnum;
    string cardname;
public:
    void setCardNum(int);
    void setCardName(string);
    int getCardNum() {return cardnum;}
    string getCardName() {return cardname;}
};

#endif /* CARDS_H */

