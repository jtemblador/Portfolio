/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Players.h
 * Author: Jose Temblador
 *
 * Created on July 30, 2021, 5:39 PM
 */
#include "User.h"
#include "Dealer.h"
#include <iostream>
#ifndef PLAYERS_H
#define PLAYERS_H

class Player:public User {
private: 
    string plyr,
           dealer;
    int plyhnd,
        dlrhnd;
    User player;
    Dealer dlr;
public:
    Player();
    Player(string a, string b, int c, int d) {
        player.setName(a);
        player.setHand(c);
        dlr.setHand(d);
        
        plyr=player.getName();
        dealer="The Dealer";
        plyhnd=player.gethand();
        dlrhnd=dlr.getHand();
    }
    void sendData() {
        printData(plyr, dealer, plyhnd, dlrhnd);
    }
};

#endif /* PLAYERS_H */

