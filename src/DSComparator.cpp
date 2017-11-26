//============================================================================
// Name        : DSComparator.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for Discounted-sum Buchi comparator
//============================================================================

#include "BA.h"
#include "common.h"
#include "DSComparator.h"
#include "rabitUtils.h"


using namespace std;

//Accepts sequence V iff DS(v, df) > 0

BA* makeDS(int df, int* difList, int len){

  //cout  << "Entered makeDS" << endl;

  if (len == 0){
    BA* aut = new BA();
    return aut;
  }

  else{

    sort(difList, difList+len);
    
    
    int maxVal = difList[len-1];
    int minVal = difList[0];
    
    //cout << maxVal << endl;;

    int maxX = ceil(maxVal/floor(df-1)) + 1;
    int maxC = ceil((float(df)/float(df-1))*maxVal);
    //cout << maxX << " " << maxC << endl;

    unordered_map <string, int> stateMap;
    unordered_map <string, int> valMap;
    vector<int>* finalList = new vector <int> {};
    int num = 0;

    //Setting up all states
    stateMap["start"] = num;
    vector <int>* initList = new vector <int> {num};
    num += 1;

    string botState = "";
    string accState = "";
    string bot = "b";
    
    for (int i= (-1*maxX); i <= maxX; i++){
      //cout << i << endl;
      accState = to_string(i);
      botState = bot + accState;

      stateMap[accState] = num;
      valMap[accState] = i;
      finalList->push_back(num);
      num += 1;

      stateMap[botState] = num;
      valMap[botState] = i;
      num += 1;
    }

    //Beginning transitions
    
    unordered_map<int, vector <Transition*> > *  transFunction = new unordered_map<int, vector <Transition*> > {};
    // start is the 0-th state
    //(*transFunction)[0] = new vector <Transition* > {};
    int highx;
    string stateid;
    int val;
    Transition* trans;
    for (int lowx = (-1*maxX); lowx <= maxX; lowx++){
      highx = lowx + maxC;
      for (int j = 0; j < len ; j++){
	val = difList[j];
	if (lowx <= val){
	  if (lowx == val){
	    // lowx == difList[j]
	    // from start state, when transition move into botstate
	    stateid = bot + to_string(lowx);
	    trans = new Transition(0, stateMap[stateid], to_string(val));
	    (*transFunction)[0].push_back(trans);
	    //trans->toString();
	    //cout << val << " " << stateid << endl;
	  }
	  else {
	    if (val <= highx){
	    // lowx < val <= highx
	    // from start state, when transition move into accepting state
	    stateid = to_string(lowx);
	    trans = new Transition(0, stateMap[stateid], to_string(val));
	    (*transFunction)[0].push_back(trans);
	    //trans->toString();
	    //cout << val << " " <<  stateid << endl;
	    }
	  }
	}
      }
    }

    int low;
    int high;
    string stateid1;
    string stateid2;
    //unordered_map <int, vector <Transition*> > botToBotTrans;
    //unordered_map <int, vector <Transition*> > botToAccTrans;
    //unordered_map <int, vector <Transition*> > accToAccTrans;
    for (int x1 = (-1*maxX); x1 <= maxX; x1++){
      for (int x2 = (-1*maxX); x2 <= maxX; x2++){
	low = x2 - df*x1;
	high = low + df;
	for (int k = 0; k < len; k++){
	  val = difList[k];
	  if (low <= val){
	    if (low == val){
	      // Transitions from bot-x1 to bot-x2 on val
	      stateid1 = bot + to_string(x1);
	      stateid2 = bot + to_string(x2);
	      trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
	      (*transFunction)[stateMap[stateid1]].push_back(trans);
	      // Transitions from x1 to x2 on val
	      stateid1 = to_string(x1);
	      stateid2 = to_string(x2);
	      trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
	      (*transFunction)[stateMap[stateid1]].push_back(trans);
	    }
	    else {
	      if (val <= high){
		// Transitions from bot-x1 to x2 on val
		stateid1 = bot + to_string(x1);
		stateid2 = to_string(x2);
		trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
	        (*transFunction)[stateMap[stateid1]].push_back(trans);
		// Transitions from x1 to x2 on val
		stateid1 = to_string(x1);
		stateid2 = to_string(x2);
		trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
	        (*transFunction)[stateMap[stateid1]].push_back(trans);
	      }
	    }
	  }
	}
      }
    }

    //Making state list
    /*
    vector <int> * stateList = new vector <int> {};
    for (int n=0; n< num; n++){
      stateList->push_back(n);
    }
    */

    //Making alpha list
    vector <string> * alphaList = new vector <string> {};
    for (int n = 0; n < len; n++){
      alphaList->push_back(to_string(difList[n]));
    }
    //TODO
    //Check with all some smal comparator value
    //Make an unordered_map of all transitions, and construct the relevant BA
    /*
    this->numState = num;
    this->alphabet = *initList;
    this->final = *finalList;
    this->initial = *initList;
    this->transFunc = *transFunction;
    */
    //BA(num,initList, finalList, alphaList, transFunction);
    BA* aut  = new BA(num,initList, finalList, alphaList, transFunction);
    return aut;
  }
}

BA* makeDSComparator(vector<string>* alphaList, int df, string filename){

  //cout <<  "Entered makeDSComparator" << endl;
  int numAll = alphaList->size();
  int elem;
  int numUnique = 0;
  int ar[numAll];
  bool present = 0;
  string delimiter = ";;";
  string alpha;
  for (int i = 0; i < numAll; i++){
    alpha = (*alphaList)[i];
    //cout << alpha << endl;
    alpha.erase(0, alpha.find(delimiter)+2);
    //cout << alpha << endl;
    elem = stoi(alpha.substr(0, alpha.find(delimiter)));
    //cout << elem << endl;
    
    for (int j=0; j<numUnique; j++){
      //cout << "Check " << ar[j] << endl;
      if (elem == ar[j]){
	present = 1;
      }
    }
    if (!present){
      ar[numUnique] = elem;
      numUnique += 1;
    }
    present = 0;
  }

  for (int n = 0; n < numUnique; n++){
    //cout << ar[n] << endl;
  }
  BA* dsaut = reduce(makeDS(df, ar, numUnique), filename);
  //BA* dsaut = makeDS(df, ar, numUnique);
  //dsaut->printAll();
  return dsaut;
}
/*

DS::~DS(){
  //TODO
}

*/
