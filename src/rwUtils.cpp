//============================================================================
// Name        : Utils.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Utility functions for QIP
//============================================================================

//#include <iostream>
//#include <string>

#include "BA.h"
#include "common.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"


using namespace std;


// Takes filename as input (file.txt)
// Reads file and generates the corresponding weighted automata
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




// Takes filename as input (file.txt)
// Reads file and generates the corresponding weighted automata
BA* readBA(string filename){
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
  //string wtStr;
  Transition* ptrTrans;
  vector <Transition*> ptrTransList = {};

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
  
      destStr = x.erase(0, index+delimiter2Len);
      //index = x.find(delimiter1);
      //destStr = x.substr(0, index);
    
      //wtStr = x.erase(0, index+delimiter1Len);
    

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

      ptrTrans = new Transition(stateMap[stoi(srcStr)], stateMap[stoi(destStr)], alpha);
     
      ptrTransList.push_back(ptrTrans);
     
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

  
  BA* inputBA = new BA(numState, numInit, numState, k, initList, finalList, alphaList, &ptrTransList); 
  return inputBA;
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

  vector<string> reachState = {};

  
  for(it1 = init1->begin(); it1!= init1->end(); ++it1){
    //cout << (*init1)[*it1] << endl;
    for(it2 = init2->begin(); it2!= init2->end(); ++it2){
      //cout << (*init1)[*it1] << " " << (*init2)[*it2] << endl;
      ss = to_string((*init1)[*it1]);
      ss += sep;
      ss += to_string((*init2)[*it2]);
      stateMap[ss] = numState;
      reachState.push_back(ss);
      //cout << ss << " " << stateMap[ss]<< " " << reachState.size() << endl;
      //(*prodTrans)[ss] =  vector<Transition*> {};
      ss = "";
      numState += 1;
      numInit += 1;
    }
  }

  unordered_map<int, vector<Transition*>>* prodTrans = new unordered_map<int, vector<Transition*>> {};
  vector <string>* alphaList = new vector<string>{};
  unordered_map<int, vector<Transition*>>*  aut1Trans = aut1->getTrans();
  unordered_map<int, vector<Transition*>>*  aut2Trans = aut2->getTrans();
  int aut1NumTrans = aut1Trans->size();
  int aut2NumTrans = aut2Trans->size();

  string stateStr;
  string str1;
  string str2;
  int s1;
  int s2;
  int p;
  int len1;
  int len2;
  Transition* transprod;
  Transition* trans1;
  Transition* trans2;
  string dest1;
  string dest2;
  int d1;
  int d2;
  string alpha1;
  string alpha2;
  string alphaprod;
  string alphasep = ";;";
  
  for (int k = 0; k < reachState.size(); k++){
    stateStr = reachState[k];
    (*prodTrans)[stateMap[stateStr]] =  vector<Transition*> {};
    p = stateStr.find(sep);
    str1 = stateStr.substr(0, p);
    str2 = stateStr.erase(0, p+1);
    s1 = stoi(str1);
    s2 = stoi(str2);

    //Look at transition list from state s1 in aut1 and s2 in aut2
    // make the new transition, and add that to s1_s2
    // look at the destination of new transition. If destination is already in reachState, we are fine, else add it to reachState and assign its state number in stateMap
    len1 = (*aut1Trans)[s1].size();
    len2 = (*aut2Trans)[s2].size();
    for (int t1 = 0; t1 < len1; t1++){
      for (int t2 = 0; t2 < len2; t2++){
	trans1  = (*aut1Trans)[s1][t1];
	trans2  = (*aut2Trans)[s2][t2];

	alpha1 = trans1->getAlpha();
	alpha2 = trans2->getAlpha();
	//cout << alpha1 << " " << alpha2 << endl;
	if (alpha1.substr(0, alpha1.find(alphasep)) == alpha2.substr(0, alpha2.find(alphasep))){

	  //Make the product alpha
	  alphaprod = alpha1;
	  alphaprod += alpha2.substr(alpha2.find(alphasep), alpha2.size());
	  alphaList->push_back(alphaprod);
       
	  //Make the product destination
	  d1 = trans1->getDest();
	  d2 = trans2->getDest();
	  
	  ss = to_string(d1);
	  ss += sep;
	  ss += to_string(d2);
	  //cout << ss << endl;
	  
	  if (stateMap[ss] == -1){
	    stateMap[ss] = numState;
	    numState += 1;
	    reachState.push_back(ss);
	  }

	  //Make prod transition, and add to the relevant place
	  transprod = new Transition(stateMap[reachState[k]], stateMap[ss], alphaprod);
	  (*prodTrans)[stateMap[reachState[k]]].push_back(transprod);
	  //cout << stateMap[reachState[k]] << " " << reachState[k] << " " << (*prodTrans)[stateMap[reachState[k]]].size() << endl;
	}
	alphaprod = "";
	ss = "";
      }
    }
  }
  
  //Making all states
  vector<int>* stateList = new vector<int> {};
  for(int ii = 0; ii < numState; ii++){
    stateList->push_back(ii);
  }

  //Making inital states
  vector<int>* initList = new vector<int> {};
  for(int ii = 0; ii < numInit; ii++){
    initList->push_back(ii);
  }

  BA* aut = new BA(numState, initList, stateList, alphaList, prodTrans );
  return aut;
  //BA* trivial = new BA();
  //return trivial;
}
