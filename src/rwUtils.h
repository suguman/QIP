/*
 * rwUtils.h
 *
 * Created on: November 6, 2017
 * Author: Suguman Bansal
 */


#ifndef RWUTILS_H
#define RWUTILS_H

#include "common.h"
#include "BA.h"
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

  //General string declarations
  string x;
  string delimiter = ",";
  
  //Initial state declaration
  int numInit = 0;
  bool areEqual;
  bool endInit = 0;
  vector<int> initList = {};

  //Transition function declaration
  string alpha;
  string src;
  string dest;
  string wtStr;
  int wt;
  int state = 0;
  int numalpha = 0;
  int numTrans = 0;
  //unordered_map<string, int> stateMap = {};
  //unordered_map<string, void> alphaMap = {};
  
  while (inFile >> x){

    if (!endInit){
      
      areEqual = (x.length() == (x.substr(0, x.find(delimiter))).length());
      if (areEqual){
	initList.push_back(stoi(x));
	numInit+=1;
      }
      else{
	endInit = 1;
	//cout << numInit << " " << initList.size() << endl;
      }
    }

    if (endInit){
      cout << x << endl;
    }
    
    
    //cout << x << " " << x.find(delimiter) << " " << x.substr(0, x.find(delimiter)) << " " << endl;
    //bool areEqual =  (x.length() == (x.substr(0, x.find(delimiter).length())).length());
    //cout << areEqual << endl;
  }

  inFile.close();

  wBA trivial;
  
  return trivial;
}


#endif
