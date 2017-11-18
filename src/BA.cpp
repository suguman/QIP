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
  
  
}


BA::BA(int num, vector<int>* initList, vector<int>* finalList, vector<string>* alphaList, unordered_map<int, vector<Transition*> >* transMap){
  this->numState = num;
  this->alphabet = *alphaList;
  this->initial = *initList;
  this->final = *finalList;
  this->transFunc = *transMap;
}

BA::BA(int num, vector<int>* initList, vector<int>* finalList, vector<string>* alphaList, vector <Transition*>* transList){
  this->numState = num;
  this->alphabet = *alphaList;
  this->initial = *initList;
  this->final = *finalList;

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

void BA::setAlphabet(vector<string>* alphaList){
  this->alphabet = *alphaList;
}


void BA::setTrans(unordered_map<int, vector<Transition*>>* transitionF){
  this->transFunc = *transitionF;
}


void BA::writeToFile(string filename){
  ofstream outFile;
  outFile.open(filename+".ba");

  string initStr = "";
  vector <int> * initList = this->getInitial();
  int numInit = initList->size();
  for (int i = 0; i < numInit; i++){
    initStr = "["+to_string((*initList)[i]) + "]\n";
  }
  outFile << initStr;
  outFile.flush();

  string transStr = "";
  int numTrans = 0;
  int flushInt = 1;
  Transition* trans;
  unordered_map <int, vector<Transition*>>* transMap = this->getTrans();
  int num = this->getStateNum();
  for (int j = 0 ; j < num ; j++){
    numTrans = (*transMap)[j].size();
    for (int k = 0; k < numTrans; k++){
      trans = (*transMap)[j][k];
      transStr += trans->getAlpha() + ",[" + to_string(trans->getSrc()) + "]->[" + to_string(trans->getDest()) + "]\n";
      flushInt += 1;
      if (flushInt%10000 == 0){
	outFile << transStr;
	outFile.flush();
	transStr = "";
	flushInt = 1;
      }
    }
  }
  outFile << transStr;
  outFile.flush();
  
  string finalStr = "";
  vector<int>* finalList = this->getFinal();
  int numFinal = finalList->size();
  for (int l = 0; l < numFinal; l++){
    finalStr += "["+to_string((*finalList)[l]) + "]\n";
  }
  outFile << finalStr;
  outFile.flush();
    
  outFile.close();
}


void BA::writeDSToFile(string filename){
  //To deal with -ve val numbers since RABIT cannot read them
  
  ofstream outFile;
  outFile.open(filename+".ba");

  string initStr = "";
  vector <int> * initList = this->getInitial();
  int numInit = initList->size();
  for (int i = 0; i < numInit; i++){
    initStr = "["+to_string((*initList)[i]) + "]\n";
  }
  outFile << initStr;
  outFile.flush();

  string transStr = "";
  int numTrans = 0;
  int flushInt = 1;
  Transition* trans;
  string alphaAux;
  unordered_map <int, vector<Transition*>>* transMap = this->getTrans();
  int num = this->getStateNum();
  for (int j = 0 ; j < num ; j++){
    numTrans = (*transMap)[j].size();
    for (int k = 0; k < numTrans; k++){
      trans = (*transMap)[j][k];
      alphaAux = trans->getAlpha()[0];
      if (alphaAux == "-"){
	transStr += "n"+trans->getAlpha().substr(1) + ",[" + to_string(trans->getSrc()) + "]->[" + to_string(trans->getDest()) + "]\n";
      }
      else {
	transStr += trans->getAlpha() + ",[" + to_string(trans->getSrc()) + "]->[" + to_string(trans->getDest()) + "]\n";
      }
      flushInt += 1;
      if (flushInt%10000 == 0){
	outFile << transStr;
	outFile.flush();
	transStr = "";
	flushInt = 1;
      }
    }
  }
  outFile << transStr;
  outFile.flush();
  
  string finalStr = "";
  vector<int>* finalList = this->getFinal();
  int numFinal = finalList->size();
  for (int l = 0; l < numFinal; l++){
    finalStr += "["+to_string((*finalList)[l]) + "]\n";
  }
  outFile << finalStr;
  outFile.flush();
    
  outFile.close();
}
