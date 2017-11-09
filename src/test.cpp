//#include <iostream>
//#include <string>
//#include <vector>


//#include "common.h"



#include "BA.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"

int main (){
 

  Transition* mytrans = new Transition();
  (*mytrans).toString();
  mytrans = new Transition(1, 2, "a");
  (*mytrans).toString();
  mytrans = new wTransition();
  (*mytrans).toString();
  mytrans = new wTransition(2, 4, "a", 5);
  (*mytrans).toString();
  //(&mytrans).toString();
  
  vector< Transition > transList;


  vector<Transition* > test;
  test.push_back(mytrans);
  test[0]->toString();

  Transition* mytrans2 = new wTransition(1, 2, "a", 10);
  test.push_back(mytrans2);
  (*test[1]).toString();
  wTransition* newP = (wTransition*) mytrans2;
  cout<< newP->getWt() << endl;
  
  int ar1[] = {8,9,10,11,12};
  int ar2[] = {5,3};
  string ar3[] = {"a", "b", "c", "d"};
  
  wBA aut2(8, 5, 2, 4,  ar1, ar2, ar3, &test);
  //aut2.printAll();
 
return 0;
}
