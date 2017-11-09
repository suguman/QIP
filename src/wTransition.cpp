//============================================================================
// Name        : wTransition.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for (weighted) transitions
//============================================================================


#include "common.h"
//#include "Transition.h"
#include "wTransition.h"

using namespace std;


wTransition::wTransition():
  Transition(){
  //srcState = 0;
  //destState = 0;
  //alpha = "NA";
  this->wt = 0;
}


wTransition::wTransition(int s, int d, string a, int w):
  Transition(s, d, a){
  this->wt = w;
}

wTransition::~wTransition(){
  // TODO
}


int wTransition::getWt(){
  return wt;
}

void wTransition::setWt(int w){
  this->wt = w;
}


void wTransition::toString(){
  
  cout << getSrc();
  cout << "-->" ;
  cout << getAlpha() ;
  cout << "--" ;
  cout << getWt();
  cout << "-->";
  cout << getDest() << endl ;
  //cout << "Hello world" << endl;
  //cout << endl;
}

