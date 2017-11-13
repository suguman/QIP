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
