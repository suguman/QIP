//============================================================================
// Name        : DSGame.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Functions for solving discounted-sum game
//============================================================================


#include "BA.h"
#include "common.h"
#include "memory.h"
#include "rwUtils.h"
#include "timers.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"

#include <chrono>

using namespace std;

string GLPKPath = "../../Tools/glpk-4.63/";

float readOutFile(string filename){
  //TODO read output file

  ifstream inFile;
  string x;
  
  inFile.open(filename);
  if (!inFile){
    cerr << "Unable to open file" << endl;
    exit(1);
  }

  while (inFile >> x){
    //cout << x << endl;
    
    if (x.substr(0,6) == "Status"){
      //cout << x << endl;
      inFile >> x;
      //cout << x << endl;
      if (x == "OPTIMAL"){
	//Objective line
	inFile >> x;
	//obj line
	inFile >> x;
	//= line
	inFile >> x;
	//val line
	inFile >> x;
	return stof(x);
      }
      else {
	//Non-negative value
	return 0;
      }
    }
    
  }

  return 0;
}

float runGLPK(string filename){
  string cmd = GLPKPath + "/examples/./glpsol --cpxlp " + GLPKPath + filename + ".lp -o "+filename+".out";
  system(cmd.c_str());
  float minWt = readOutFile(filename+".out");
  //int minWt = 0;
  string rmfiles = "rm "+ GLPKPath + filename + ".lp  "+filename+".out";
  system(rmfiles.c_str());
  return minWt;
}


string createGame(int df, wBA* aut, string filename){

  if ((aut->getStateNum() == 0) ||
      ((aut->getInitial())->size() == 0) ||
      ((aut->getFinal())->size() == 0)){

    
    //outFile.flush();
    //outFile.close();
    return 0;
  }
   
  int numState = aut->getStateNum();
  cout << numState << endl;

  string ss;
  string sep = "_";

  cout << "Before initialization " << cpuTimeTotal() << endl;

  //int countMem = 1;
  
  //cout << "Mem at initial " << getPhysicalMem() << endl;
  //cout << "Time at init " << cpuTimeTotal() << endl;
  unordered_map <string, int> wtMap;
  for (int i=0; i < numState; i++){
    for (int j=0; j < numState; j++){
      ss = to_string(i) + sep + to_string(j);
      wtMap[ss] = INT_MAX;
      //countMem += 1;
      //if (countMem % 1000000 == 0){
	//cout << "Mem at initial " << getPhysicalMem() << endl;
	//cout << "Time at init " << cpuTimeTotal() << endl;
	//countMem = 1;
      //}
      //cout << ss << " " << wtMap[ss] << endl;
    }
  }

  cout << "Initialize required constraints " << cpuTimeTotal() << endl;

  int dest;
  int wt;
  int temp;
  unordered_map<int, vector<Transition*>>* transMap = aut->getTrans();
  for (int i = 0; i < numState; i++){
    for (Transition* trans : (*transMap)[i]){
      //trans->toString();
      dest = trans->getDest();
      wt = trans->getWt();
      ss = to_string(i) + sep + to_string(dest);
      if (wtMap[ss] > wt){
	wtMap[ss]  = wt;
      }
    }
  }
  
  //double endSetLP = cpuTotalTime();
  cout << "Logged the required constraints " << cpuTimeTotal() << endl;
  /*
    Write file for game
  */

  string lpfile = GLPKPath + filename + ".lp";
  ofstream outFile;
  outFile.open(lpfile);
  
  string newline = "\n";
  string var = "x";
  string leq = "<=";
  string minus = "-";

  string varName1;
  string varName2;

  string objective = "Maximize"+newline;
  objective += var + to_string((*aut->getInitial())[0]) + newline;
  //TODO Wrtie objective to file
  //cout << objective;
  outFile << objective;
  outFile.flush();
    
  cout << "Begin writing constraints " << cpuTimeTotal() << endl;
  string constraint = "Subject to" + newline;
  int counter = 1;
  for (int i=0; i < numState; i++){
    for (int j=0; j < numState; j++){
      ss = to_string(i) + sep + to_string(j);
      if (wtMap[ss] != INT_MAX){
	counter += 1;
	//cout << ss << " " << wtMap[ss] << endl;;
	if (i==j){
	  //cout << ss << "  equal " << wtMap[ss] << endl;
	  constraint += to_string(df-1) + var + to_string(i) + leq + to_string(wtMap[ss]) + newline;
	  /*
	    new equation is (df-1)*i  <= wtMap[ss]
	  */
	}
	else {
	  //cout << ss << " not equal " << wtMap[ss] << endl;
	  constraint += to_string(df) + var + to_string(i) + minus + var + to_string(j) + leq + to_string(wtMap[ss]) + newline;
	  /*
	    new equation is df*i - j <= wtMap[ss]
	  */
	}
      }
      if (counter%10000 == 0){
	//TODO Wrtie constraint to file
	//cout << constraint;
	double beginFlush = cpuTimeTotal();
	outFile << constraint;
	//double beginFlush = cpuTimeTotal();
	outFile.flush();
	double endFlush = cpuTimeTotal();
	cout << "Flush times " << beginFlush << " " << endFlush << " " << endFlush-beginFlush << endl;
	counter = 1;
	constraint = "";
      }
    }
  }
  //TODO Wrtie constraint to file
  //cout << constraint;
  double beginFlush = cpuTimeTotal();
  outFile << constraint;
  outFile.flush();
  double endFlush = cpuTimeTotal();
  cout << "Flush times " << beginFlush << " " <<  endFlush << " " << endFlush - beginFlush << endl;
  
  //TODO Wrtie constraint to file
  string endline = "End\n";
  //cout << endline;
  outFile << endline;
  outFile.flush();

  outFile.close();
  cout << "End writing constraints " << cpuTimeTotal() << endl;
  //double beginLP = cpuTimeTotal();
  auto beginLP = chrono::high_resolution_clock::now();
  float val  = runGLPK(filename);
  //double endLP = cpuTimeTotal();
  auto endLP = chrono::high_resolution_clock::now();
  //cout << val << endl;
  double t = (chrono::duration_cast<chrono::milliseconds>(endLP - beginLP).count())/1000.0;
  return to_string(val)+"_" + to_string(t);
}



