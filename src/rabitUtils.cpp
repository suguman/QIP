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


BA* reduce(string filename){
 
  string reduceCommand = "java -Xss1G -Xms1G -jar " + RABITPATH + "Reduce.jar " + filename + ".ba 30";
  system(reduceCommand.c_str());
  BA* reducedBA = readBA("reduced_30_"+filename + ".ba");
  string removeFile = "rm " + filename + ".ba " + "reduced_30_" + filename + ".ba";
  system(removeFile.c_str());
  return reducedBA;
}

bool checkEqui(BA* aut1, BA* aut2, string filename1, string filename2){
  aut1->writeToFile(filename1);
  aut2->writeToFile(filename2);
  string equi1command = "java -jar " + RABITPATH + "RABIT.jar " + filename1 + ".ba " + filename2 + ".ba > "+filename1+filename2+"output.txt";
  system(equi1command.c_str());

  ifstream inFile;
  inFile.open(filename1+filename2+"output.txt");
  string x;
  inFile >> x;
  string removeFileCommand = "rm " + filename1 + ".ba " + filename2 + ".ba " + filename1+filename2+"output.txt";
  if (x[0] == 'N'){
    //system(removeFileCommand.c_str());
    return 0;
  }
  //system(removeFileCommand.c_str());
  return 1;
}


/*

import os
from automata import *
from fileToBA import *
#import subprocess
#from subprocess import STDOUT, check_output

RABITPATH = "../Tools/RABIT"
#RABITPATH = "/RABIT"
DUMPDIR = "DUMP/"
workDir = os.path.dirname(os.path.realpath(__file__)) 
def minimize(DSAut, filename):
       DSAut.baWrite(filename)
       
       #Reduce size of automata      
       rabitCommand = "java -Xss1G -Xms1G -jar "+RABITPATH+"/Reduce.jar " +   filename+".ba 30"
       os.system(rabitCommand)
       #subprocess.call(rabitCommand, shell=True)
       #output = check_output(rabitCommand, stderr=STDOUT, shell = True, timeout=20)
       DSAutRed = convertToBA("reduced_30_"+filename+".ba")
       os.system("rm reduced_30_"+filename+".ba "+filename+".ba")
       return DSAutRed


*/
