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
  //Note :: current implementation of sameAlphaProd can result in duplication of transitions in the output. This is becaue we do not check if the transition is already present in the transition function before inserted it. 

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

  vector<int>* init1 = aut1->getInitial();
  vector<int>* init2 = aut2->getInitial();
  int aut1InitLen = init1->size();
  int aut2InitLen = init2->size();
  
  vector<string> reachState = {};

  //aut->printInitial();
  //comp->printInitial();
  
  for (int it1 = 0; it1 < aut1InitLen; it1++){
    for (int it2 = 0; it2 < aut2InitLen ; it2++){
      ss = to_string((*init1)[it1]);
      ss += sep;
      ss += to_string((*init2)[it2]);

      cout << ss << endl;
      stateMap[ss] = numState;
      reachState.push_back(ss);
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

	  //posA is length of common alphabet in both alphabets since they are the same
	  
	  int posA = alpha1.find(alphasep);
	  //Make the product alpha
	  int dlen = alphasep.size();
	  alphaprod = alpha1.substr(0, posA+dlen);
	  int wt1 = stoi(alpha1.substr(posA+dlen));
	  alpha2.erase(0, posA+dlen);
	  int wt2 = stoi(alpha2.substr(0, dlen));
	  alpha2.erase(0, alpha2.find(alphasep));
	  alphaprod += to_string(wt1 - wt2);
	  alphaprod += alpha2;
	  
	  /*
	  //This construction of alphaprod doesn't take the difference of weights. It simply concatenates them
	  alphaprod = alpha1;
	  alphaprod += alpha2.substr(alpha2.find(alphasep), alpha2.size());
	  */
	  
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
	  //TODO
	  //Include the new transition only if the same transition hasn't been inserted before. Is it even worth doing?
	  
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


BA* intersectSelAlpha(BA* aut, BA* comp){

  int autState = aut->getStateNum();
  int compState = comp->getStateNum();
  //int numprodstate = aut->getStateNum() * comp->getStateNum();
  string ss = "";
  string sep = "_";

  unordered_map<string, int> stateMap;
  for (int i=0; i < autState; i++){
    for (int j=0; j< compState; j++){
      ss = to_string(i);
      ss += sep;
      ss += to_string(j);
      stateMap[ss] = -1;
      ss = "";
    }
  }

  int numState = 0; 
  int numInit = 0;
  
  
  
  vector<int>* init1 = aut->getInitial();
  vector<int>* init2 = comp->getInitial();
  int autInitLen = init1->size();
  int compInitLen = init2->size();
  
  vector<string> reachState = {};

  //aut->printInitial();
  //comp->printInitial();
  
  for (int it1 = 0; it1 < autInitLen; it1++){
    for (int it2 = 0; it2 < compInitLen ; it2++){
      ss = to_string((*init1)[it1]);
      ss += sep;
      ss += to_string((*init2)[it2]);

      //cout << ss << endl;
      stateMap[ss] = numState;
      reachState.push_back(ss);
      ss = "";
      numState += 1;
      numInit += 1;
      
    }
  }

  unordered_map<int, vector<Transition*>>* intersectTrans = new unordered_map<int, vector<Transition*>> {};
  vector <string>* alphaList = new vector<string>{};
  unordered_map<int, vector<Transition*>>*  autTrans = aut->getTrans();
  unordered_map<int, vector<Transition*>>*  compTrans = comp->getTrans();
  int autNumTrans = autTrans->size();
  int compNumTrans = compTrans->size();

  string stateStr;
  string str1;
  string str2;
  int s1;
  int s2;
  int p;
  int len1;
  int len2;
  string wtStr;
  Transition* transprod;
  Transition* trans1;
  Transition* trans2;
  string dest1;
  string dest2;
  int d1;
  int d2;
  string alpha1;
  string alpha2;
  string alphaproject;
  string alphasep = ";;";
  int alphaseplen = 2;
  
  for (int k = 0; k < reachState.size(); k++){
    stateStr = reachState[k];
    (*intersectTrans)[stateMap[stateStr]] =  vector<Transition*> {};
    p = stateStr.find(sep);
    str1 = stateStr.substr(0, p);
    str2 = stateStr.erase(0, p+1);
    s1 = stoi(str1);
    s2 = stoi(str2);

    //Look at transition list from state s1 in aut1 and s2 in aut2
    // make the new transition, and add that to s1_s2
    // look at the destination of new transition. If destination is already in reachState, we are fine, else add it to reachState and assign its state number in stateMap
    len1 = (*autTrans)[s1].size();
    len2 = (*compTrans)[s2].size();
    for (int t1 = 0; t1 < len1; t1++){
      for (int t2 = 0; t2 < len2; t2++){
	trans1  = (*autTrans)[s1][t1];
	trans2  = (*compTrans)[s2][t2];

	//trans1->toString();
	//trans2->toString();

	//Also creating new alphabet for the projection. Removing the weight vector
	alpha1 = trans1->getAlpha();
	//cout << alpha1 << endl;
	alphaproject = alpha1.substr(0, alpha1.find(alphasep));
	alpha1.erase(0, alpha1.find(alphasep)+ alphaseplen);
	wtStr = alpha1.substr(0, alpha1.find(alphasep));
	alphaproject += alpha1.substr(alpha1.find(alphasep));

	alpha2 = trans2->getAlpha();
	//cout << alphaproject << " " << wtStr << " " << alpha2 << " " <<  endl;
		
	//cout << alpha1 << " " << alpha2 << endl;
	if (wtStr == alpha2){
	
	  alphaList->push_back(alphaproject);
	   
	  
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
	  //cout << "new transition " << endl;
	  transprod = new Transition(stateMap[reachState[k]], stateMap[ss], alphaproject);
	  //transprod->toString();
	  //cout << reachState[k] << " " << ss << endl;
	  (*intersectTrans)[stateMap[reachState[k]]].push_back(transprod);
	  //TODO
	  //Include the new transition only if the same transition hasn't been inserted before. Is it even worth doing?
	  
	}
	alphaproject = "";
	ss = "";
      }
    }
  }
  

  //Making final states
  
  vector<int>* finalComp = comp->getFinal();
  int lenFinal = finalComp->size();

  vector <int>* finalList = new vector<int> {};
  for (int ai = 0; ai < autState; ai++){
    for (int ci = 0; ci < lenFinal; ci++){
      ss = to_string(ai);
      ss += sep;
      ss += to_string((*finalComp)[ci]);
      //cout << "Final state is " << ai << " " << (*finalComp)[ci] << " State is " << stateMap[ss] <<endl;
      if (stateMap[ss] != -1){
	finalList->push_back(stateMap[ss]);
      }
    }
  }

  //Making inital states
  vector<int>* initList = new vector<int> {};
  for(int ii = 0; ii < numInit; ii++){
    initList->push_back(ii);
  }
  
  BA* intersect = new BA(numState, initList, finalList, alphaList,  intersectTrans );
  return intersect;
}

void projectOutWt(BA* aut){
  //Project out wt component in place. Modify all alphabet from alpha;;wt;;label to alpha;;label in transitions and alphabet in place.
  //No need to allocate new memory

  //project Map
  unordered_map <string, string> projectMap;
  vector <string>* alphaList = aut->getAlpha();
  vector <string>* newAlphaList = new vector<string> {};
  int numAlpha = alphaList->size();
  string alphaproject;
  string alpha;
  string sep = ";;";
  int sepLen = 2;
  for (int i = 0; i < numAlpha; i++){
    alpha = (*alphaList)[i];
    //cout << alpha << endl;
    alphaproject = alpha.substr(0, alpha.find(sep)+sepLen);
    alpha.erase(0, alpha.find(sep)+2);
    alphaproject += alpha.erase(0,alpha.find(sep)+2);
    //cout << alphaproject << " " << alpha << endl;
    projectMap[(*alphaList)[i]] = alphaproject;
    newAlphaList->push_back(alphaproject);
  }

  //aut->alphabet = *newAlphaList;
  aut->setAlphabet(newAlphaList);
  

  int numState = aut->getStateNum();
  int numTrans;
  Transition* trans;
  Transition* newTrans;
  unordered_map<int, vector<Transition*> > * transitionF = aut->getTrans();
  unordered_map<int, vector<Transition*> > * newTransF = new unordered_map <int, vector<Transition*> >  {};
  for (int j = 0; j < numState; j++){
    (*newTransF)[j] = vector <Transition*> {};
    numTrans = (*transitionF)[j].size();
    for (int k=0; k < numTrans; k++){
      trans = (*transitionF)[j][k];
      trans->toString();
      newTrans = new Transition (trans->getSrc(), trans->getDest(), projectMap[trans->getAlpha()]);
      (*newTransF)[j].push_back(newTrans);
      newTrans->toString();
	
    }
  }

  aut->setTrans(newTransF);
  
}
