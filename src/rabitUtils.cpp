//============================================================================
// Name        : Utils.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Utility functions for running RABIT in QIP
//============================================================================

#include "BA.h"
#include "common.h"
#include "rwUtils.h"
#include "Transition.h"
#include "wBA.h"
#include "wTransition.h"

using namespace std;

string RABITPATH = "../../Tools/RABIT/";


//BA* reduce(string filename){
BA* reduce(BA* aut){
  aut->writeDSToFile("DS");
  string reduceCommand = "java -Xss1G -Xms1G -jar " + RABITPATH + "Reduce.jar DS.ba 30";
  system(reduceCommand.c_str());
  BA* reducedBA = readBA("reduced_30_DS.ba");
  string removeFile = "rm DS.ba reduced_30_DS.ba";
  system(removeFile.c_str());
  return reducedBA;
}

int checkEqui(BA* aut1, BA* aut2, string outputfile){
  aut1->writeToFile(outputfile+"_0");
  aut2->writeToFile(outputfile+"_1");
  
  string equi1command = "java -jar " + RABITPATH + "RABIT.jar " +  outputfile+"_0.ba " + outputfile+"_1.ba  > " + outputfile+"_3.txt ";
  system(equi1command.c_str());

  ifstream inFile;
  inFile.open(outputfile+"_3.txt");
  string x;
  inFile >> x;
 
  string removeFileCommand = "rm " + outputfile+"_0.ba " + outputfile+"_1.ba " + outputfile+"_3.txt";

  system(removeFileCommand.c_str());
  
  if (x[0] == 'N'){  
    return 0;
  }
  if (x[0] == 'I'){  
    return 1;
  }
  //When RABIT-Reduce fails to solve inclusion
  return 2;
}



