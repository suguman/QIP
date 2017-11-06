//#include <iostream>
//#include <string>
//#include <vector>


//#include "common.h"

#include "BA.h"
#include "Transition.h"


int main (){
  Transition trans;
  Transition trans2(2,2,"a");
  Transition trans3(2, 3, "a");
  trans.toString();
  trans2.toString();

  vector< Transition > transList;
  transList.push_back(trans);
  transList.push_back(trans2);
  transList.push_back(trans3);
  
  BA aut;

  int ar1[] = {8,9,10,11,12};
  int ar2[] = {5,3};
  string ar3[] = {"a", "b", "c", "d"};
  
  BA aut2(5, 5, 2, 4,  ar1, ar2, ar3, &transList);

  cout << sizeof(string) << endl;
  //cout << sizeof(int) << endl;
  aut2.printInitial();
  aut2.printFinal();
  aut2.printAlpha();
  //cout << aut2.transFunc[0].size()<< endl;
  //cout << aut2.transFunc[4].size() << endl;
  //cout << aut2.getStateNum() << endl;
  //cout << aut2.getInitial()[0] << endl;
  //cout << aut2.getInitial()[1] << endl;
  //cout << aut2.getInitial()[2] << endl;
return 0;
}
