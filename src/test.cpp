//#include <iostream>
//#include <string>
//#include <vector>


//#include "common.h"

#include "BA.h"
#include "Transition.h"
#include "wTransition.h"

int main (){
  Transition trans;
  Transition trans2(2,2,"a");
  Transition trans3(2, 3, "a");
  //trans.toString();
  //trans2.toString();
  wTransition wTrans;
  wTrans.toString();
  cout << wTrans.getSrc() << endl;
  wTrans.setSrc(5);
  cout << wTrans.getSrc() << endl;
  wTrans.toString();
  wTrans.setWt(6);
  wTrans.toString();
  cout << wTrans.getWt() << endl;
  vector< Transition > transList;
  transList.push_back(trans);
  transList.push_back(trans2);
  transList.push_back(trans3);

  //Transition wtrans2;
  //wtrans2.setWt(6);
  
  BA aut;

  int ar1[] = {8,9,10,11,12};
  int ar2[] = {5,3};
  string ar3[] = {"a", "b", "c", "d"};
  
  BA aut2(8, 5, 2, 4,  ar1, ar2, ar3, &transList);

  //cout << sizeof(string) << endl;
  //cout << sizeof(int) << endl;
  //aut2.printInitial();
  //aut2.printFinal();
  //aut2.printAlpha();

  //cout <<  aut2.getTrans() << endl;
  //unordered_map<int, vector<Transition> > tFunction;
  //tFunction = *(aut2.getTrans());
  //aut2.printTrans();
  //aut2.printAll();
  //cout << (aut2.getTrans()).size()<< endl;
  //cout << (aut2.getTrans())[3].size()<< endl;
  //cout << (aut2.transFunc)[4].size() << endl;
  //cout << aut2.getTrans()[4].size() << endl;
  //cout << aut2.getStateNum() << endl;
  //cout << aut2.getInitial()[0] << endl;
  //cout << aut2.getInitial()[1] << endl;
  //cout << aut2.getInitial()[2] << endl;
return 0;
}
