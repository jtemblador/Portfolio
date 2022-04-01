/* 
 * File:   main.cpp
 * Author: Jose Temblador
 * Created on July 27, 2021, 10:50 AM
 * Purpose:  Project 2
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random number generator
#include <iomanip>   //Formats output
#include <cmath>     //Math library
#include <ctime>     //Time Library 
#include <string>    //String Library
#include <fstream>   //File Input/Output Library
using namespace std;

//User Libraries

#include "User.h"
#include "Dealer.h"
#include "Cards.h"
#include "CopyClass.h"
#include "Players.h"

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void dlrHnd (string [], CardInfo [], int [], int , bool, int &, int &,
             Dealer &, unsigned char =0); //Gets dealer's hand
void HorF (string [], CardInfo [], int &, int, bool, User &, int []); //Asks player to hit/fold
bool checkAce (unsigned char &, bool , User);   //Player check ace function
bool linSrch (string [], int [], int [], int , int );    //Linear Search Function
bool checkAceDlr (unsigned char &, bool , int );        //Dealer checkAce function 
unsigned char rndmNum(unsigned char);   //Finds random number
void SlSort(int [], int );              //Sorts the array 
int *Fill (int [], int);                //creates and fills array 
void PrintHand(int *, int, CardInfo []);//Prints users hand
string ReadFile(fstream &input);

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    const unsigned char nCards=52;  //number of cards in a deck
    const unsigned char MAXCARD=10; //Max number of cards a player can hold in their hand
    unsigned char rawnum=0;         //random number that is generated each time random function is called
    const int SIZE=20;
    int cardnum1=0,                 //Card index number 1
        cardnum2=1,                 //Card index number 2
        dlrhand,                    //Dealer's hand
        crdnms1[MAXCARD],           //name of card for index 1
        crdnms2[MAXCARD],           //name of card for index 2
        *crdnm1ptr=crdnms1;               //pointer array that points to hand of player 1
    string allcards[nCards+1],//Array of all card suits and numbers
           cards[nCards+1],   //array of cards that are read in
           dlr[nCards+1],     //dealer's cards 
           winner,      //winner at the end of the game (user or dealer)
           rsltOut="results.dat",  //Output winner/loser
           nmrdin,
           dName="The Dealer";//string to be passed into dealer class 
    bool ace=false;    //true if player has an ace, false if ont   
    User player;    //Player 
    Dealer dealer(dName, 0); //dealer class contains name and hand value
    CardInfo crdsfile[nCards];//array of classes, these are the card names and numbers
    
    //Variables for reading and writing to files
    fstream input, 
            out,        //Reads out game results at the end of the game
            binName;    //binary file that reads in name and writes to a string
    string  cardIn,     //string array that stores all the names of the cards locally
            fileName="card.dat",//file where card are stored
            nameIn  ="name.dat";//file where name is stored

    input.open(fileName.c_str(),ios::in);
    
    for (int i=1; i<=nCards; i++) {
        input>>cardIn;          //file is read in and assigns 
        crdsfile[i].setCardNum(i);//sets number for card read in
        crdsfile[i].setCardName(cardIn);//sets name for card read in
    }

    input.close();
/************************************************************************************/    
    cout<<"Your name is being read through a file.\n";
    
    nmrdin=ReadFile(input); //name is being read in 
    player.setName(nmrdin); //name is copied to player structure
    
    cout<<"Player "<<player.getObjCnt()<<" is "<<player.getName()<<"."<<endl;//char array is called 
    cout<<"*********************************************************************\n";
    cout<<"Your hand is currently at: "<<player.gethand()<<endl;
    
    int card1, card2;
    //drawing first card
    rawnum=rndmNum(nCards);             //gets a random card number
    crdnm1ptr[0]=rawnum;         //random card number is put into an array (players hand)
    cards[0]=crdsfile[rawnum].getCardName();   //assigns random card from card set to player hand
    rawnum=rawnum%13;       //Mods card number by 13 to give it a value

    ace=checkAce(rawnum, ace, player);    //Checks to see if player has ace

    if (rawnum==0||rawnum==11||rawnum==12||rawnum==13) //Face cards equal 10
        card1=10;
    else if (rawnum==14)   //first ace card is worth 11
        card1=11;
    else card1=rawnum;  //every other card is assigned its number value
    cout<<"Card number 1 is  "<<cards[0]<<endl<<
          "Your hand is    "<<setw(3)<<card1<<endl<<endl;    
    
    //Drawing second card
    rawnum=rndmNum(nCards);             //gets a random card number
    crdnm1ptr[1]=rawnum;         //random card number is put into an array (players hand)
    cards[1]=crdsfile[rawnum].getCardName();   //assigns random card from card set to player hand
    rawnum=rawnum%13;       //Mods card number by 13 to give it a value

    ace=checkAce(rawnum, ace, player);    //Checks to see if player has ace

    if (rawnum==0||rawnum==11||rawnum==12||rawnum==13) //Face cards equal 10
        card2=10;
    else if (rawnum==14)   //first ace card is worth 11
        card2=11;
    else card2=rawnum;  //every other card is assigned its number value
    
    player.setHand(card1, card2);

    cout<<"Card number 2 is  "<<cards[1]<<endl<<
          "Your hand is    "<<setw(3)<<player.gethand()<<endl<<endl;    
    
    if (player.gethand()==21) //If hand reaches 21 after 2 cards, go straight to dealer turn
        cout<<"Looks like your hand is already at 21\n"
              "Lets see what the dealer has.\n";
    else HorF(cards, crdsfile, cardnum1, nCards, ace, player, crdnms1);//asks user if they want to continue
    cout<<"*********************************************************************\n";
    ace=false;
    dlrHnd (dlr, crdsfile, crdnms2, nCards, ace, cardnum2, dlrhand, dealer, rawnum);
    cout<<"*********************************************************************\n";

    SlSort(crdnms1, cardnum1);              //Sorts the players hand
    int *srtarry=Fill(crdnms1, cardnum1);   //Fills a dynamic array with the sorted array
    User cpyplyr(player);
    cout<<cpyplyr.getName()<<", your cards in order are as follows. (Hearts>Clubs>Diamonds>Spades)\n";
    PrintHand(srtarry, cardnum1, crdsfile);           //Prints the dynamic array
    
    out.open(rsltOut,ios::out);
    
    User plus=player;
    plus++;
    cout<<endl<<"Incrementing player's hand by operator overloading: "<<plus.gethand()<<endl;
    User minus=player;
    minus--;
    cout<<"Decrementing player's hand by operator overloading: "<<minus.gethand()<<endl;
    
    User aa;
    aa.setHand(dealer.getHand());
    User addclss;
    addclss=player+aa;
    cout<<"Adding player and dealer's hands together: "<<addclss.gethand()<<endl;
    
    Player a(player.getName(), dealer.getName(), player.gethand(), dealer.getHand());
    a.sendData();
    
    cout<<"\nThe game is over!\n";
    cout<<"Results are displayed in the output file named 'results.dat'\n";  

    out<<"Your hand is         "<<player.gethand()<<".\n";         //displays hand of user 
    out<<dealer.getName()<<"'s hand is "<<dealer.getHand()<<".\n";//displays hand of dealer 
 
            //If user and dealer hand is over 21, nobody wins
            //If user or dealer hand is over 21, opponent wins
            //If user and dealer below 21, both hands are compared and 
            //greatest hand is determined the winner
            //If user wins, displays amount won
    
    if ((player.gethand()>21)&&(dealer.getHand()>21)) 
        out<<"You and the dealer went over. Nobody wins!\n";
    else if (player.gethand()>21) 
        out<<"You went over, the Dealer wins!"<<endl;
    else if (dealer.getHand()>21) 
    {
        out<<fixed<<setprecision(2);
        out<<"The Dealer went over, "<<cpyplyr.getName()<<" wins!"<<endl;
    }
    else
    {       //Ternary operator to determine winner
        (player.gethand()>dealer.getHand())? out<<"Congrats "<<cpyplyr.getName()<<", you won!":
        (dealer.getHand()>player.gethand())? out<<dealer.getName()<<" won.":
            out<<"Tie! Nobody won.";
    }
    
    //Exit the Program - Cleanup
    //No dynamic arrays to delete 
    input.close();
    out.close();
    return 0;
}

string ReadFile(fstream &input) {
    string namerdin;
    input.open("name.dat", ios::in);    //Name file opened
    getline(input, namerdin);           //Name is read in from file to a string
    input.close();      //close file
    return namerdin;
}

void PrintHand(int *array, int size, CardInfo crdsfile[]) {
    for (int i=0; i<size; i++) {
        cout<<"Card "<<i+1<<" is "<<crdsfile[*(array+i)].getCardName()<<endl;
    }
}

int *Fill(int a[],int n) {
    int *array= new int [n]; //Creating Dynamic Array
    for(int i=0; i<n; ++i)
        array[i]=a[i];       //Filling dynamic array of previously sorted array
    return array;            //returning dynamic array
}

void SlSort(int a[],int n){
    for(int i=0;i<n;i++){      //Loop for each position in List
        int idxMin=i;
        for(int j=i+1;j<n;j++){  //Loop to swap with first in List
            if(a[idxMin]>a[j]){  //Put the smallest at top of List
                idxMin=j;
            }
        }
        int temp=a[i];
        a[i]=a[idxMin];
        a[idxMin]=temp;
    }
}

void dlrHnd (string dlr[], CardInfo crdsfile[], int crdnms2[], int nCards, bool ace, 
             int &cardnum2, int &dlrhand,  Dealer &dealer, unsigned char rawnum) {
    
    //dealer.setHand(0);
    cout<<"It is now the Dealers turn.\n"<<endl;
    
    while (dealer.getHand()<=16) {      //Once dealer reaches 16 or greater, loop ends                      
        rawnum=rndmNum(nCards);         //gets a random card number
        crdnms2[cardnum2]=rawnum;       //Raw Card number is put into an array (players hand)
        dlr[cardnum2]=crdsfile[rawnum].getCardName(); //assigns random card from card set to player hand
        rawnum=rawnum%13;               //Mods card number by 13 to give it a value
        
        ace=checkAceDlr(rawnum, ace, dealer.getHand());    //Checks to see if player has ace
        
        if (rawnum==0||rawnum==11||rawnum==12||rawnum==13) //Face cards equal 10
            dealer.setHand(10);
        else if (rawnum==14)   //first ace card is worth 11
            dealer.setHand(11);
        else dealer.setHand(rawnum);  //every other card is assigned its number value
        
        cout<<"Card "<<cardnum2<<" is "<<dlr[cardnum2]<<".\n";
        cout<<dealer.getName()<<" is at "<<dealer.getHand()<<".\n"<<endl;
        cardnum2++;
    } 
    
}

bool checkAceDlr (unsigned char &rawnum, bool ace, int a){//Dealer's checkAce function
    if (rawnum==1)
    {
        if (ace==true)
        {  //player can only have 1 ace card worth 11, every other ace card after is worth 1
            cout<<"Dealer already have an ace card.\n"
                  "This card will be worth 1.\n";
            return true;
        }
        else if ((a+rawnum+10)>21)
        {   //if hand goes over 21, ace is worth 1
            cout<<"Dealer doesn't have an Ace, but he'll go over"<<
            " if it's counted as 11. This one counts as 1."<<endl;
            return false;
        }
        else 
        {   //if first ace and hand is under 21, ace is worth 11
            cout<<"Dealer got an Ace.\n";
            rawnum=14;
            return true;
        }
    }
    return false;
}

void HorF(string cards[], CardInfo crdsfile[], int &cardnum1, int nCards, 
          bool ace, User &player, int crdnms1[]) {
    unsigned char decide;
    unsigned char rawnum=0;
    cout<<"Would you like to hit or fold?"<<endl<<
          "Type 'H' to hit or any other key to fold"<<endl;
        cin>>decide;
        if (decide>47&&decide<57) {
            throw "Invalid decision!\n";
        }
        cout<<endl;
        if (static_cast<int>(decide)=='h')  decide-=32;
        
        for (cardnum1=2;decide=='H'&&player.gethand()<21;cardnum1++)  //Only repeats if decision is hit or
    {                                                   //hand is below 21
        rawnum=rndmNum(nCards);             //gets a random card number
        crdnms1[cardnum1]=rawnum;            //Raw Card number is put into an array (players hand)
        cards[cardnum1]=crdsfile[rawnum].getCardName();
        rawnum=rawnum%13;       //Mods card number by 13 to give it a value
        
        ace=checkAce(rawnum, ace, player);    //Checks to see if player has ace
        
        if (rawnum==0||rawnum==11||rawnum==12||rawnum==13) //Face cards equal 10
            player.setHand(10); 
        else if (rawnum==14)   //first ace card is worth 11
            player.setHand(11);
        else player.setHand(rawnum);  //every other card is assigned its number value
        
        cout<<"Card number "<<cardnum1+1<<" is  "<<cards[cardnum1]<<endl<<
              "Your hand is    "<<setw(3)<<player.gethand()<<endl<<endl;
        
        if (player.gethand()<21)
        {               //Asks player to hit or fold
            cout<<"Would you like to hit or fold?"<<endl<<
                  "Type H to hit or any other key to fold"<<endl;
            cin>>decide;
            if (decide>47&&decide<57) {
                throw "Invalid decision!\n";
            }   
            if (static_cast<int>(decide)=='h')  decide-=32;
        }
    }
}

bool checkAce (unsigned char &rawnum, bool ace, User player) {//User's checkAce function
    if (rawnum==1)
    {
        if (ace==true)
        {  //player can only have 1 ace card worth 11, every other ace card after is worth 1
            cout<<"Looks like you already have an ace card.\n"
                  "This card will be worth 1.\n";
            return true;
        }
        else if ((player.gethand()+rawnum+10)>21)
        {   //if hand goes over 21, ace is worth 1
            cout<<"You don't have an Ace, but you will go over"<<
            " if it's counted as 11. This one counts as 1."<<endl;
            return false;
        }
        else 
        {   //if first ace and hand is under 21, ace is worth 11
            cout<<"Your luck! Looks like you got an Ace.\n";
            rawnum=14;
            return true;
        }
    }
    return false;
}

unsigned char rndmNum(unsigned char nCards) {
    return rand()%nCards+1; //Gets a random number from 1-52
}
