/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CopyClass.cpp
 * Author: mac
 *
 * Created on July 31, 2021, 3:48 PM
 */
#include "CopyClass.h"
#include <cstdlib>
using namespace std;

template <class T>
CopyClass <T>::CopyClass() {
    copyname="";
}

template <class T>
void CopyClass <T>::setCopyName(string name) {
    copyname=name;
}

template <class T>
string CopyClass <T>::getCopyName() {
    return copyname;
}

