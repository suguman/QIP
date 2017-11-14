/*
 * wBA.h
 *
 * Created on: November 6, 2017
 * Author: Suguman Bansal
 */


#ifndef WBA_H
#define WBA_H

#include "common.h"
#include "BA.h"
#include "wTransition.h"


using namespace std;

class wBA: public BA{

public:

  wBA();
  
  wBA(int num, int numInit, int numFinal, int numAlpha, int* pInit, int *pFinal, string pAlpha[], vector<Transition*>* transList);
  
  wBA(int num, vector<int>* initList, vector<int>* finalList, vector<string>* alphaList, unordered_map<int, vector<Transition*> >* transMap);
  
  virtual ~wBA();
  
  
  vector<int> getWeight();
  //void getWeight();

  void printWeight();

  
  BA* augmentWt();
  BA* augmentWtLabel();
  
};


#endif
