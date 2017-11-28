//============================================================================
// Name        : DSGame.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Functions for solving discounted-sum game
//============================================================================


#include "BA.h"
#include "common.h"
#include "rwUtils.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"

using namespace std;

string GLPKPath = "../../Tools/glpk-4.63/";

int readOutFile(string filename){
  //TODO read output file
}

int runGLPK(string filename){
  string cmd = "glpsol --cpxlp " + GLPKPath + filename + ".lp -o "+filename+".out";
  system(cmd.c_str());
  //int minWt = getMinWeight(filename+".out");
  int minWt = 0;
  string rmfiles = "rm "+ GLPKPath + filename + ".lp  "+filename+".out";
  system(rmfiles.c_str());
  return minWt;
}


int createGame(int df, wBA* aut, string filename){

  if ((aut->getStateNum() == 0) ||
      ((aut->getInitial())->size() == 0) ||
      ((aut->getFinal())->size() == 0)){

    
    //outFile.flush();
    //outFile.close();
    return -1;
  }
   
  int numState = aut->getStateNum();
  //cout << numState << endl;

  string ss;
  string sep = "_";
  
  unordered_map <string, int> wtMap;
  for (int i=0; i < numState; i++){
    for (int j=0; j < numState; j++){
      ss = to_string(i) + sep + to_string(j);
      wtMap[ss] = INT_MAX;
      //cout << ss << " " << wtMap[ss] << endl;
    }
  }

  
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
      if (counter%2 == 0){
	//TODO Wrtie constraint to file
	//cout << constraint;
	outFile << constraint;
	outFile.flush();
	counter = 1;
	constraint = "";
      }
    }
  }
  //TODO Wrtie constraint to file
  //cout << constraint;
  outFile << constraint;
  outFile.flush();
  
  //TODO Wrtie constraint to file
  string endline = "End\n";
  //cout << endline;
  outFile << endline;
  outFile.flush();

  outFile.close();

  int val  = runGLPK(filename);
  cout << val << endl;
  return val;
}



