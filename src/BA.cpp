//============================================================================
// Name        : BA.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for Buchi automata 
//============================================================================

#include <iostream>
#include <string>
#include <vector>

#include "BA.h"

using namespace std;

BA::BA(){
  this->numState = 0;
  //alphabet = {};
  this->initial = {};
  this->final = {};
  //transFunc = {};
}

BA::BA(int num,  int numInit, int numFinal, int *pInit, int *pFinal){
  this->numState = num;
  //alphabet = &alpha;
  /*
  int i;
  for(i=0; i<num; i++){
    cout << *(pInit+i) << "\n";
    initial.push_back(*(pInit+i));
  }
  */
  int* beginInit = pInit;
  int* endInit = pInit + numInit;
  this->initial = vector<int> (beginInit, endInit);

  int* beginFinal = pFinal;
  int* endFinal = pFinal + numFinal;
  this->final = vector<int> (beginFinal, endFinal);

}

BA::~BA(){
  //TODO
}

int BA::getStateNum(){
  return numState;
}

vector<int> BA::getInitial(){
    return initial;
}

vector<int> BA::getFinal(){
    return final;
}

void BA::printFinal(){
  vector<int> finalList = this->getFinal();
  int len = finalList.size();
  cout << "Final states are : ";
  for (int i = 0; i < len; i++){
    cout << finalList[i] << ", ";
  }
  cout << endl;
}

void BA:: printInitial(){
  vector<int> initialList = this->getInitial();
  int len = initialList.size();
  cout << "Initial states are : ";
  for (int i = 0; i < len; i++){
    cout << initialList[i] << ", ";
  }
  cout << endl;
}
