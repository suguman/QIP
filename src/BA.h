/*
 * BA.h
 *
 * Created on: November 2, 2017
 * Author: Suguman Bansal
 */

#ifndef BA_H
#define BA_H

//#include <string>
//#include <vector>


#include "common.h"
#include "Transition.h"

using namespace std;

class BA{

 public:
  BA();
  BA(int num, int numInit, int numFinal, int numAlpha, int* pInit, int *pFinal, string pAlpha[], vector<Transition>* transList);
  virtual ~BA();

  int getStateNum();
  vector<int> getInitial();
  vector<int> getFinal();
  vector<string> getAlpha();
  
  void printInitial();
  void printFinal();
  void printAlpha();
  
 private:
  int numState;
  vector<string> alphabet;
  vector<int> initial;
  vector<int> final;
  unordered_map<int, vector<Transition>> transFunc;
  // transFunc needs to change to Hash map - unordered map
  
};


#endif 
