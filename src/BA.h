/*
 * BA.h
 *
 * Created on: November 2, 2017
 * Author: Suguman Bansal
 */

#include <string>
#include <vector>
#include "Transition.h"

using namespace std;

class BA{

 public:
  BA();
  virtual ~BA();

  

 private:
  int numStates;
  string alphabet[];
  vector<int> initial;
  vector<int> final;
  vector<Transition> transFunc;
  // transFunc needs to change to Hash map - unordered map
  
};
