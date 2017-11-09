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

wBA::~wBA(){
  //TODO
}
vector<int>* wBA::getWeight(){
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
  return &wtList;
  
}

void wBA::printWeight(){
  //TODO
}



