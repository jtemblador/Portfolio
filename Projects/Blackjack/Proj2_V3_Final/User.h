/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: mac
 *
 * Created on July 19, 2021, 3:21 AM
 */

#ifndef USER_H
#define USER_H
#include <string>
using namespace std;


class User {
    protected:
        string name;
        string copyname;
        int hand;
        static int objCnt;
    public:
        User();
        User (User &);
        ~User();
        void setName(string);       //sets players name
        void setHand(int);          //adds one card to players hand
        void setHand(int, int);     //add two cards to players hand
        int gethand() {return hand;}//returns hand
        string getName() {return name;}//returns name
        void setCopyName(User &);   //copies name from another class
        string getCopyName();   //returns name of player
        int getObjCnt();        //static int, counts how many players there are
        void printData(string, string, int, int); //prints data 
        const User operator ++(int) {
            hand++;
            return *this;
        }//operator for incrementing players hand
        const User operator --(int) {
            hand--;
            return *this;
        }//operator for decrementing players hand
        User operator +(User a) {
            User sum;
            sum.setHand(a.gethand()+gethand());
            return sum;
        } ////operator for adding User class together
};


#endif /* USER_H */

