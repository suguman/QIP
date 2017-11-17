//============================================================================
// Name        : wBA.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for weighted Buchi automata 
//============================================================================


#include "common.h"
#include "wBA.h"

using namespace std;


wBA::wBA():
  BA(){}


wBA::wBA(int num, int numInit, int numFinal, int numAlpha, int* pInit, int *pFinal, string pAlpha[], vector<Transition*>* transList):
  BA(num, numInit, numFinal,  numAlpha,  pInit, pFinal, pAlpha, transList){}

wBA::wBA(int num, vector<int>* initList, vector<int>* finalList, vector<string>* alphaList, unordered_map<int, vector<Transition*> >* transMap):
  BA(num, initList, finalList, alphaList, transMap){}

wBA::~wBA(){
  //TODO
}
vector<int> wBA::getWeight(){
  unordered_map <int, vector<Transition* > >* transF =  this->getTrans();
  int num = this->getStateNum();
  unordered_set<int> wtSet = {};
  int numTrans = 0;
  int wtVal = 0;
  wTransition* ptrTransTemp;
  for (int i = 0; i< num; i++){
    numTrans = (*transF)[i].size();
    for (int j=0; j<numTrans; j++){
      
      ptrTransTemp = (wTransition*) (*transF)[i][j];
      wtVal = ptrTransTemp->getWt();
      wtSet.insert(wtVal);
      
    }
  }
  vector<int> wtList = vector<int> (wtSet.begin(), wtSet.end());
  cout << wtSet.size() << endl;
  cout << wtList.size() << endl;
  return wtList;
  
}

void wBA::printWeight(){
  //TODO
}

BA* wBA::augmentWt(){

  string sep = ";;";
  
  int numState = this->getStateNum();
  vector<int>* initList = this->getInitial();
  //vector<string>* alphaList = this->getAlpha();
  vector<string>* alphaList = new vector<string> {};
  vector<int>* finalList = this->getFinal();
  unordered_map<int, vector< Transition*>> * wtransMap = this->getTrans();

  Transition* trans;
  string str;

  unordered_map<int , vector<Transition*>>* transMap = new unordered_map<int, vector<Transition*>> {};
  
  for (int i=0; i< numState; i++){
    (*transMap)[i] = vector<Transition*> {};
  }

  int numTrans = 0;
  for (int j=0; j< numState; j++){
    numTrans = (*wtransMap)[j].size();
   
    for (int k=0; k < numTrans; k++){
      wTransition* ptrTrans = (wTransition*) (*wtransMap)[j][k];
      
      str = ptrTrans->getAlpha();
      str += sep;
      str += to_string(ptrTrans->getWt());

      trans = new Transition(j, ptrTrans->getDest(), str);

      (*transMap)[j].push_back(trans);
      alphaList->push_back(str);
      }
  }

  BA* augmentAut = new BA(numState, initList, finalList, alphaList, transMap);
 
  return augmentAut;
}



BA* wBA::augmentWtLabel(){

  string sep = ";;";
  
  int numState = this->getStateNum();
  vector<int>* initList = this->getInitial();
  //vector<string>* alphaList = this->getAlpha();
  vector <string>* alphaList = new vector<string> {};
  vector<int>* finalList = this->getFinal();
  unordered_map<int, vector< Transition*>> * wtransMap = this->getTrans();

  Transition* trans;
  string str;
 
  int totalTrans = 0;
  
  unordered_map<int , vector<Transition*>>* transMap = new unordered_map<int, vector<Transition*>> {};
  
  for (int i=0; i< numState; i++){
    (*transMap)[i] = vector<Transition*> {};
  }

  int numTrans = 0;
  for (int j=0; j< numState; j++){
    numTrans = (*wtransMap)[j].size();
   
    for (int k=0; k < numTrans; k++){
      wTransition* ptrTrans = (wTransition*) (*wtransMap)[j][k];
      
      str = ptrTrans->getAlpha();
      str += sep;
      str += to_string(ptrTrans->getWt());
      str += sep;
      str += to_string(totalTrans);
      
      totalTrans += 1;

      trans = new Transition(j, ptrTrans->getDest(), str);
      alphaList->push_back(str);
      //cout << str << " " << alphaList->size() << endl;
      (*transMap)[j].push_back(trans);
      
      }
  }

  BA* augmentAut = new BA(numState, initList, finalList, alphaList, transMap);
 
  return augmentAut;
}
