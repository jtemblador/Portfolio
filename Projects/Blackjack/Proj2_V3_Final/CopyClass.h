/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CopyClass.h
 * Author: mac
 *
 * Created on July 31, 2021, 3:47 PM
 */

#ifndef COPYCLASS_H
#define COPYCLASS_H
#include <string>
using namespace std;

template <class T>
class CopyClass {
private:
    string copyname;
public:
    CopyClass();
    ~CopyClass();
    void setCopyName(string);
    string getCopyName();
};

#endif /* COPYCLASS_H */

