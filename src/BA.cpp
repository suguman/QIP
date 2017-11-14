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

  for (int i=0; i < num; i++){
    this->transFunc[i] = vector<Transition*> {};
  }
  int len = (*transList).size();
  int src = 0;
  for (int j=0; j < len; j++){
    src = (*(*transList)[j]).getSrc();
    //(*transList)[j]->toString();
    (this->transFunc)[src].push_back((*transList)[j]);
    
  }
  //End of the new code
  
}

BA::BA(int num, vector<int>* initList, vector<int>* finalList, vector<string>* alphaList, unordered_map<int, vector<Transition*> >* transMap){
  this->numState = num;
  this->alphabet = *alphaList;
  this->initial = *initList;
  this->final = *finalList;
  this->transFunc = *transMap;
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

unordered_map<int, vector<Transition*> >* BA::getTrans(){ 
  return &(this->transFunc);
}

void BA::printFinal(){
  vector<int> finalList = *(this->getFinal());
  int len = finalList.size();
  //cout <<  len << endl;
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

  
  unordered_map<int, vector<Transition*> > tFunction = *(this->getTrans());
  //cout << &tFunction << endl;
  int num = this->getStateNum();
  int numTrans = 0;
  for (int i=0; i< num; i++){
    numTrans = tFunction[i].size();
    cout << "Number of transitions from state " << i << " are " << numTrans << endl;
    for (int j=0; j < numTrans; j++){
    
      //cout << (tFunction[i][j]) << endl;
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
