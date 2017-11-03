/*
 * BA.h
 *
 * Created on: November 2, 2017
 * Author: Suguman Bansal
 */

#include <string>
#include <vector>
//#include "Transition.h"

using namespace std;

class BA{

 public:
  BA();
  BA(int num, int numInit, int numFinal, int* pInit, int *pFinal);
  virtual ~BA();

  int getStateNum();
  vector<int> getInitial();
  vector<int> getFinal();

  void printInitial();
  void printFinal();
 private:
  int numState;
  //vector<string> alphabet;
  vector<int> initial;
  vector<int> final;
  //vector<Transition> transFunc;
  // transFunc needs to change to Hash map - unordered map
  
};
