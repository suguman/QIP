/*
 * wTransition.h
 *
 * Created on: November 6, 2017
 * Author: Suguman Bansal
 */


#ifndef WTRANSITION_H
#define WTRANSITION_H

#include "common.h"
#include "Transition.h"

using namespace std;

class wTransition: public Transition{

public:

  //TODO ALL
  wTransition();
  //wTransition(int s, int d, string a, int w): Transition(int s, int d, string a);
  //wTransition(int s, int d, string a, int w);
  virtual ~wTransition();
  
  //int getSrc();
  //int getDest();
  //string getAlpha();
  int getWt();

  //void setSrc(int s);
  //void setDest(int d);
  //void setAlpha(string a);
  void setWt(int w);
  
  void toString();

private:
  //int srcState;
  //int destState;
  //string alpha;
  int wt;
};


#endif
