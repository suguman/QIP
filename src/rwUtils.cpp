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




wBA readWBA(string filename){
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
  //vector<int> initList = {};
  int numInit = 0;

  //Transition function declarations
  string alpha;
  string srcStr;
  string destStr;
  string wtStr;
  wTransition wtrans;
  vector <wTransition> wTransListTemp = {};
  vector <Transition*> wTransList = {};
  //unordered_map<int, vector<Transition*> > tFunc;
  
  //int wt;
  //int state = 0;
  //int numalpha = 0;
  //int numTrans = 0;
  //unordered_map<string, int> stateMap = {};
  //unordered_map<string, void> alphaMap = {};
  
  while (inFile >> x){

    if (!endInit){
      
      areEqual = (x.length() == (x.substr(0, x.find(delimiter1))).length());
      if (areEqual and !endInit){
	got = stateMap.find(stoi(x));
	//got = stateMap.find(x);
	if (got == stateMap.end()){
	  stateMap.insert({stoi(x),numState});
	  //stateMap.insert({x,numState});
	  //initList.push_back(numState);
	  numState+=1;
	  numInit+=1;
	  //cout << "Printing length of stateMap " << stateMap.size() << endl ;
	}

      }
      else{
	//Indicates that all the initial states have been read. The current read is not an initial state. It is a transition. 
	endInit = 1;
	//cout << numInit << " " << initList.size() << endl;
      }
    }

    if (endInit){

      //parsing transition line
      //cout << x << endl;
      int index = x.find(delimiter1);
      alpha = x.substr(0, index);
      //cout << alpha << endl;
      x.erase(0, index + delimiter1Len);
      index = x.find(delimiter2);
      srcStr = x.substr(0, index);
      //cout << srcStr << endl;
      x.erase(0, index+delimiter2Len);
      index = x.find(delimiter1);
      destStr = x.substr(0, index);
      //cout << destStr << endl;
      wtStr = x.erase(0, index+delimiter1Len);
      //cout << wtStr << endl;

      //src State
      got = stateMap.find(stoi(srcStr));
      //got = stateMap.find(srcStr);
      if (got == stateMap.end()){
	//stateMap.insert({srcStr,numState});
	stateMap.insert({stoi(srcStr),numState});
	numState+=1;
	//initList.push_back(numState);
	//cout << "Printing length of stateMap " << stateMap.size() << endl ;
      }

      //dest State
      got = stateMap.find(stoi(destStr));
      //got = stateMap.find(destStr);
      if (got == stateMap.end()){
	stateMap.insert({stoi(destStr),numState});
	//stateMap.insert({destStr,numState});
	numState+=1;
	//initList.push_back(numState);
	//cout << "Printing length of stateMap " << stateMap.size() << endl ;
      }

      got2 = alphaMap.find(alpha);
      if (got2 == alphaMap.end()){
	alphaMap.insert({alpha,0});
	//alphaList.push_back(alpha);
	//initList.push_back(numState);
	//cout << "Printing length of alpha " << alphaMap.size() << endl ;
      }

      //Making transition

  
      wtrans  = wTransition(stateMap[stoi(srcStr)], stateMap[stoi(destStr)], alpha, stoi(wtStr));
      wtrans.toString();
      wTransListTemp.push_back(wtrans);
      cout << wTransListTemp.size() << endl;
      //cout << wtrans << endl;
      
    }

    //wtrans->toString();
    
    //cout << x << " " << x.find(delimiter) << " " << x.substr(0, x.find(delimiter)) << " " << endl;
    //bool areEqual =  (x.length() == (x.substr(0, x.find(delimiter).length())).length());
    //cout << areEqual << endl;
  }

  // Making the pointer list for transitions
  for (int i=0; i < wTransListTemp.size(); i++){
      wTransList.push_back(&wTransListTemp[i]);
      cout << wTransList[i] << endl;
      wTransList[i]->toString();
  }

  // Making integer list for initial states,  since first states to be read are initial states
  int initList[numInit];
  for(int j=0; j < numInit; j++){
    initList[j] = j;
    //cout << initList[j] << endl;
  }
  //cout << &initList << endl;

  // Making alpha list from alphaList, which is a vector
  int k = 0;
  string alphaList[alphaMap.size()];
  for (auto it = alphaMap.cbegin(); it != alphaMap.cend(); ++it){
    alphaList[k] = it->first;
    k+=1;
    //cout << "k value is " << k << endl;;
  }
  //cout << alphaList << endl;
  
  inFile.close();

  cout << numState << endl;
  cout << numInit << endl;
  cout << numState << endl;
  cout << &initList << endl;
  cout << &alphaList << endl;
  cout << &wTransList << endl;
  cout << wTransList.size() << endl;

  cout << wTransList[0] << endl;
  cout << wTransList[1] << endl;
  cout << wTransList[2] << endl;
  wTransList[0]->toString();
  wTransList[1]->toString();
  wTransList[2]->toString();
  cout << &wTransList << endl;
  //cout << wTransList[0].toString() << endl;
  wBA trivial(numState, numInit, numState, k, initList, initList, alphaList, &wTransList); 
  //wBA trivial;
  return trivial;
}
