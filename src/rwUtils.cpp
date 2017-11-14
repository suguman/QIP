//============================================================================
// Name        : Transition.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for (unweighted) transitions
//============================================================================

//#include <iostream>
//#include <string>

#include "BA.h"
#include "common.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"


using namespace std;



wBA* readWBA(string filename){
  ifstream inFile;
  
  inFile.open(filename);
  if (!inFile){
    cerr << "Unable to open file" << endl;
    exit(1);
  }

  //General declarations
  string x;
  string delimiter1 = ",";
  int delimiter1Len = 1;
  string delimiter2 = "->";
  int delimiter2Len = 2;
  int numState = 0;
  
  unordered_map<string, int> alphaMap = {};
  unordered_map<string, int>::const_iterator got2;
  //vector <string> alphaList = {};
  
  //state map
  unordered_map <int, int> stateMap;
  unordered_map<int, int>::const_iterator got;
  
  //Initial state declarations
  bool areEqual;
  bool endInit = 0;
  int numInit = 0;

  //Transition function declarations
  string alpha;
  string srcStr;
  string destStr;
  string wtStr;
  wTransition* ptrWTrans;
  vector <Transition*> ptrWTransList = {};

  while (inFile >> x){

    if (!endInit){
      
      areEqual = (x.length() == (x.substr(0, x.find(delimiter1))).length());
      if (areEqual and !endInit){
	got = stateMap.find(stoi(x));
	if (got == stateMap.end()){
	  stateMap.insert({stoi(x),numState});
	  numState+=1;
	  numInit+=1;
	}

      }
      else{ 
	endInit = 1;
	
      }
    }

    if (endInit){

      //parsing transition line
      
      int index = x.find(delimiter1);
      alpha = x.substr(0, index);
 
      x.erase(0, index + delimiter1Len);
      index = x.find(delimiter2);
      srcStr = x.substr(0, index);
  
      x.erase(0, index+delimiter2Len);
      index = x.find(delimiter1);
      destStr = x.substr(0, index);
    
      wtStr = x.erase(0, index+delimiter1Len);
    

      //src State
      got = stateMap.find(stoi(srcStr));
      
      if (got == stateMap.end()){

	stateMap.insert({stoi(srcStr),numState});
	numState+=1;

      }

      //dest State
      got = stateMap.find(stoi(destStr));
    
      if (got == stateMap.end()){
	stateMap.insert({stoi(destStr),numState});

	numState+=1;
	
      }

      got2 = alphaMap.find(alpha);
      if (got2 == alphaMap.end()){
	alphaMap.insert({alpha,0});

      }

      //Making transition

      ptrWTrans = new wTransition(stateMap[stoi(srcStr)], stateMap[stoi(destStr)], alpha, stoi(wtStr));
     
      ptrWTransList.push_back(ptrWTrans);
     
    }
   
  }


  // Making integer list for initial states,  since first states to be read are initial states
  int initList[numInit];
  for(int j=0; j < numInit; j++){
    initList[j] = j;
   
  }
 

  // Making alpha list from alphaList, which is a vector
  int k = 0;
  string alphaList[alphaMap.size()];
  for (auto it = alphaMap.cbegin(); it != alphaMap.cend(); ++it){
    alphaList[k] = it->first;
    k+=1;
    
  }

  // Makinng final state  list -- > Right now this is all states
  int finalList[numState];
  for(int l=0; l<numState; l++){
    finalList[l] = l;
  }
  
  inFile.close();

  
  wBA* inputWBA = new wBA(numState, numInit, numState, k, initList, finalList, alphaList, &ptrWTransList); 
  return inputWBA;
}


BA* sameAlphaProd(BA* aut1, BA* aut2){

  int aut1State = aut1->getStateNum();
  int aut2State = aut2->getStateNum();
  int numprodstate = aut1->getStateNum() * aut2->getStateNum();
  string ss = "";
  string sep = "_";
  unordered_map<string, int> stateMap;
  for (int i=0; i < aut1State; i++){
    for (int j=0; j< aut2State; j++){
      ss = to_string(i);
      ss += sep;
      ss += to_string(j);
      stateMap[ss] = -1;
      ss = "";
    }
  }

  int numState = 0; 
  int numInit = 0;
  
  vector<int>::iterator it1;
  vector<int>::iterator it2;
  vector<int>* init1 = aut1->getInitial();
  vector<int>* init2 = aut2->getInitial();
  
  unordered_map<string, vector<Transition*>>* prodTrans = new unordered_map<string, vector<Transition*>> {};
  for(it1 = init1->begin(); it1!= init1->end(); ++it1){
    cout << (*init1)[*it1] << endl;
    for(it2 = init2->begin(); it2!= init2->end(); ++it2){
      cout << (*init1)[*it1] << " " << (*init2)[*it2] << endl;
      ss = to_string((*init1)[*it1]);
      ss += sep;
      ss += to_string((*init2)[*it2]);
      stateMap[ss] = numState;
      cout << ss << " " << stateMap[ss]<< endl;
      (*prodTrans)[ss] =  vector<Transition*> {};
      ss = "";
      //cout << ss << endl;
      numState += 1;
      numInit += 1;
    }
  }
  
  unordered_map<int, vector<Transition*>>*  aut1Trans = aut1->getTrans();
  unordered_map<int, vector<Transition*>>*  aut2Trans = aut2->getTrans();
  int aut1NumTrans = aut1Trans->size();
  int aut2NumTrans = aut2Trans->size();
  
  BA* trivial = new BA();
  return trivial;
}
