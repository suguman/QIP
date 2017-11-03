#include <iostream>
#include <string>
#include <vector>

#include "BA.h"
#include "Transition.h"

int main (){
  Transition trans;
  Transition trans2(1,2,"a");
  trans.toString();
  trans2.toString();

  BA aut;

  int ar1[] = {8,9,10,11,12};
  int ar2[] = {5,3};

  BA aut2(5, 5, 2, ar1, ar2);
  
  aut2.printInitial();
  aut2.printFinal();
  //cout << aut2.getStateNum() << endl;
  //cout << aut2.getInitial()[0] << endl;
  //cout << aut2.getInitial()[1] << endl;
  //cout << aut2.getInitial()[2] << endl;
return 0;
}
