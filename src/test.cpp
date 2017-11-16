//#include <iostream>
//#include <string>
//#include <vector>


//#include "common.h"



#include "BA.h"
#include "DSComparator.h"
#include "Transition.h"
#include "rwUtils.h"
#include "wBA.h"
#include "wTransition.h"

int main (){
 

  Transition* mytrans = new Transition();
  //(*mytrans).toString();
  mytrans = new Transition(1, 2, "a");
  //(*mytrans).toString();
  mytrans = new wTransition();
  //(*mytrans).toString();
  mytrans = new wTransition(2, 4, "a", 5);
  //(*mytrans).toString();
  //(&mytrans).toString();
  
  vector< Transition > transList;


  vector<Transition* > test;
  test.push_back(mytrans);
  //test[0]->toString();

  Transition* mytrans2 = new wTransition(1, 2, "a", 10);
  test.push_back(mytrans2);
  //(*test[1]).toString();
  wTransition* newP = (wTransition*) mytrans2;
  //cout<< newP->getWt() << endl;
  
  int ar1[] = {8,9,10,11,12};
  int ar2[] = {5,3};
  string ar3[] = {"a", "b", "c", "d"};
  
  wBA aut2(8, 5, 2, 4,  ar1, ar2, ar3, &test);
  //aut2.printAll();
  vector<int> myWt = aut2.getWeight();
  //cout << myWt.size() << endl;
  //cout << myWt[0] << endl;
  //cout << myWt[1] << endl;

  wBA aut1;
  aut1.addInitial(8);
  //aut1.printInitial();
  aut1.addInitial(9);
  //aut1.printInitial();

  wBA* readAut = readWBA("textfile.txt");
  //cout << readAut.getTrans() << endl; 
  //readAut.printTrans();
  readAut->printAll();

  BA* aut = readAut->augmentWt();
  aut->printAll();

  BA* autnew = readAut->augmentWtLabel();
  autnew->printAll();

  BA* autprod = sameAlphaProd(aut, autnew);
  autprod->printAll();

  BA* autba = readBA("testfile2.txt");
  //autba->printAll();

  int ar[] = {3, 7, 10};
  DS dstest = DS(4, ar, 3);
  //dstest.printAll();

 
return 0;
}
