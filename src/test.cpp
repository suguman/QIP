#include <iostream>
#include <string>
#include "Transition.h"

using namespace std;

int main(){

  
  Transition trans;
  Transition trans2(1,2,"a");
  trans.toString();
  trans2.toString();
  cout << trans.getSrc() << endl;
  cout << trans.getDest() << endl;
  cout << trans.getAlpha() << endl;

  cout << trans2.getSrc() << endl;
  cout << trans2.getDest() << endl;
  cout << trans2.getAlpha() << endl;

  trans.setSrc(3);
  cout << trans.getSrc() << endl;
  trans.setDest(4);
  cout << trans.getDest() << endl;
  trans.setAlpha("b");
  cout << trans.getAlpha() << endl;
  return 0;
}
