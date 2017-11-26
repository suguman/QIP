//============================================================================
// Name        : Transition.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for (unweighted) transitions
//============================================================================

//#include <iostream>
//#include <string>

#include "common.h"
#include "Transition.h"

using namespace std;


Transition::Transition(){
  srcState = 0;
  destState = 0;
  alpha = "NA";
}

Transition::Transition(int src, int dest, string a){
  srcState = src;
  destState = dest;
  alpha = a;
}

Transition::~Transition(){
  // TODO
}

int Transition::getSrc(){
  return srcState;
}

int Transition:: getDest(){
  return destState;
}

string Transition::getAlpha(){
  return alpha;
}

void Transition::setSrc(int s){
  srcState = s;
}

void Transition::setDest(int d){
  destState = d;
}

void Transition::setAlpha(string a){
  alpha = a;
}

void Transition::toString(){
  cout << getSrc();
  cout << "-->" ;
  cout << getAlpha() ;
  cout << "-->" ;
  cout << getDest() << endl;
  //cout << "Hello world" << endl;
  //cout << endl;
}

int Transition::getWt(){
  return 0;
}
