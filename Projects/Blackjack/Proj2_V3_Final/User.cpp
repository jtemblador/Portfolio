/* 
 * File:   User.cpp
 * Author: Jose Temblador
 *
 * Created on July 28, 2021, 8:10 PM
 */

#include <iostream>  //I/O Library
#include "User.h"
using namespace std;


User::User() {
    name="";
    hand=0;
    objCnt++;
}

User::User (User &obj) {
    name=obj.getName();
    hand=obj.gethand();
}

User::~User() {
    //cout<<"User class destructor engaged.\n";
}

void User::setHand(int a) {
    hand+=a;
}

void User::setHand(int a, int b) {
    hand+=a+b;
}

void User::setName(string a) {
    name=a;
}

void User::setCopyName(User &obj) {
    copyname=obj.getName();
}

string User::getCopyName() {
    return copyname;
}

int User::getObjCnt() {
    return objCnt;
}

int User::objCnt=0;

void User::printData(string a, string b, int c, int d) {
    cout<<endl;
    cout<<a<<"'s hand is "<<c<<endl;
    cout<<b<<"'s hand is "<<d<<endl;
}