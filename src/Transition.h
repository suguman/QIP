/*
 * Transition.h
 *
 * Created on: November 2, 2017
 * Author: Suguman Bansal
 */

#include <string>

using namespace std;

class Transition{

public:

  Transition();
  Transition(int s, int d, string a);
  virtual ~Transition();
  
  int getSrc();
  int getDest();
  string getAlpha();

  void setSrc(int s);
  void setDest(int d);
  void setAlpha(string a);
  
  void toString();

private:
  int srcState;
  int destState;
  string alpha;
  
};
