//============================================================================
// Name        : BA.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for Discounted-sum Buchi comparator
//============================================================================

#include "BA.h"
#include "common.h"
#include "DSComparator.h"


using namespace std;

DS::DS(int df, int* difList, int len){

  if (len == 0){
    BA aut = BA();
  }

  else{

    sort(difList, difList+len);
    
    
    int maxVal = difList[len-1];
    int minVal = difList[0];
    
    cout << maxVal << endl;;

    int maxX = ceil(maxVal/floor(df-1)) + 1;
    int maxC = ceil((float(df)/float(df-1))*maxVal);
    cout << maxX << " " << maxC << endl;

    unordered_map <string, int> stateMap;
    unordered_map <string, int> valMap;
    vector<int> finalList = {};
    int num = 0;

    //Setting up all states
    stateMap["start"] = num;
    vector <int> initList = vector <int> {num};
    num += 1;

    string botState = "";
    string accState = "";
    string bot = "b";
    
    for (int i= (-1*maxX); i <= maxX; i++){
      cout << i << endl;
      accState = to_string(i);
      botState = bot + accState;

      stateMap[accState] = num;
      valMap[accState] = i;
      finalList.push_back(num);
      num += 1;

      stateMap[botState] = num;
      valMap[botState] = i;
      num += 1;
    }

    //Beginning transitions
    
    unordered_map<int, vector <Transition*> > startTransition;
    // start is the 0-th state
    startTransition[0] = vector <Transition* > {};
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
	    startTransition[0].push_back(trans);
	    trans->toString();
	    cout << val << " " << stateid << endl;
	  }
	  else {
	    if (val <= highx){
	    // lowx < val <= highx
	    // from start state, when transition move into accepting state
	    stateid = to_string(lowx);
	    trans = new Transition(0, stateMap[stateid], to_string(val));
	    startTransition[0].push_back(trans);
	    trans->toString();
	    cout << val << " " <<  stateid << endl;
	    }
	  }
	}
      }
    }

    int low;
    int high;
    string stateid1;
    string stateid2;
    unordered_map <int, vector <Transition*> > botToBotTrans;
    unordered_map <int, vector <Transition*> > botToAccTrans;
    unordered_map <int, vector <Transition*> > accToAccTrans;
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
	      botToBotTrans[stateMap[stateid1]].push_back(trans);
	      // Transitions from x1 to x2 on val
	      stateid1 = to_string(x1);
	      stateid2 = to_string(x2);
	      trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
	      accToAccTrans[stateMap[stateid1]].push_back(trans);
	    }
	    else {
	      if (val <= high){
		// Transitions from bot-x1 to x2 on val
		stateid1 = bot + to_string(x1);
		stateid2 = to_string(x2);
		trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
		botToAccTrans[stateMap[stateid1]].push_back(trans);
		// Transitions from x1 to x2 on val
		stateid1 = to_string(x1);
		stateid2 = to_string(x2);
		trans = new Transition(stateMap[stateid1], stateMap[stateid2], to_string(val));
		accToAccTrans[stateMap[stateid1]].push_back(trans);
	      }
	    }
	  }
	}
      }
    }

    //TODO
    //Check with all some smal comparator value
    //Make an unordered_map of all transitions, and construct the relevant BA
    BA aut = BA();

  }
}


DS::~DS(){
  //TODO
}
