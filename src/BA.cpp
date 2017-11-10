//============================================================================
// Name        : BA.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for Buchi automata 
//============================================================================

//#include <iostream>
//#include <string>
//#include <vector>

#include "common.h"
#include "BA.h"
//#include "Transition.h"


using namespace std;

BA::BA(){
  this->numState = 0;
  this->alphabet = {};
  this->initial = {};
  this->final = {};
  this->transFunc = {};
}

//Modified for trans
//BA::BA(int num,  int numInit, int numFinal, int numAlpha,  int *pInit, int *pFinal, string* pAlpha, vector<Transition>* transList){
BA::BA(int num,  int numInit, int numFinal, int numAlpha,  int *pInit, int *pFinal, string* pAlpha, vector<Transition*>* transList){
  this->numState = num;
  
  int* beginInit = pInit;
  int* endInit = pInit + numInit;
  this->initial = vector<int> (beginInit, endInit);

  int* beginFinal = pFinal;
  int* endFinal = pFinal + numFinal;
  this->final = vector<int> (beginFinal, endFinal);

  string* beginAlpha = pAlpha;
  string* endAlpha = pAlpha + numAlpha;
  this->alphabet = vector<string> (beginAlpha, endAlpha);

  /* Commenting this bit for testing
  for (int i=0; i<num; i++){
    this->transFunc[i] = vector<Transition> {};
  }
  cout << num << endl;
  int len = (*transList).size();
  int src = 0;
  //cout << (*transList)[1].getSrc() << endl;
  //cout << (*transList).size() << endl;
  //cout << src << endl;
  for (int j=0; j<len; j++){
    src = (*transList)[j].getSrc();
    (this->transFunc)[src].push_back((*transList)[j]);
  }
  */

  //Beginning of the new code

  for (int i=0; i < num; i++){
    this->transFunc[i] = vector<Transition*> {};
  }
  int len = (*transList).size();
  int src = 0;
  for (int j=0; j < len; j++){
    src = (*(*transList)[j]).getSrc();
    (this->transFunc)[src].push_back((*transList)[j]);
  }
  //End of the new code
}

BA::~BA(){
  //TODO
}

int BA::getStateNum(){
  return this->numState;
}

vector<int>* BA::getInitial(){
  return &(this->initial);
}

vector<int>* BA::getFinal(){
  return &(this->final);
}

vector<string>* BA::getAlpha(){
  return &(this->alphabet);
}

//Commenting out for new code
//unordered_map<int, vector<Transition>>* BA::getTrans(){
unordered_map<int, vector<Transition*> >* BA::getTrans(){
  //cout << &(this->transFunc) << endl;
  return &(this->transFunc);
}
void BA::printFinal(){
  vector<int> finalList = *(this->getFinal());
  int len = finalList.size();
  cout << "Final states are : ";
  for (int i = 0; i < len; i++){
    cout << finalList[i] << ", ";
  }
  cout << endl;
}

void BA:: printInitial(){
  vector<int> initialList = *(this->getInitial());
  int len = initialList.size();
  cout << "Initial states are : ";
  for (int i = 0; i < len; i++){
    cout << initialList[i] << ", ";
  }
  cout << endl;
}

void BA::printAlpha(){
  
  vector<string> alphaList = *(this->getAlpha());
  int len = alphaList.size();
  cout << "Alphabet is : ";
  for (int i=0; i<len; i++){
    cout << alphaList[i] << ", ";
  }
  cout << endl;
  
}

void BA::printTrans(){

  //Commenting out for new code
  //unordered_map<int, vector<Transition> > tFunction = *(this->getTrans());
  unordered_map<int, vector<Transition*> > tFunction = *(this->getTrans());
  int num = this->getStateNum();
  int numTrans = 0;
  for (int i=0; i< num; i++){
    numTrans = tFunction[i].size();
    cout << "Number of transitions from state " << i << " are " << numTrans << endl;
    for (int j=0; j < numTrans; j++){
      //tFunction[i][j].toString();
      (*tFunction[i][j]).toString();
    }
  }
}

void BA::printAll(){
  this->printInitial();
  this->printAlpha();
  this->printTrans();
  this->printFinal();
}

void BA::addInitial(int i){
  vector<int>* ptrInit = this->getInitial();
  cout << ptrInit->size() << endl;
  ptrInit->push_back(i);
  cout << ptrInit->size() << endl;
}
