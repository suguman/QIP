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

bool checkEqui(BA* aut1, BA* aut2, string outputfile){
  aut1->writeToFile(outputfile+"_0");
  aut2->writeToFile(outputfile+"_1");
  //string equi1command = "java -jar " + RABITPATH + "RABIT.jar " + filename1 + ".ba " + filename2 + ".ba > "+filename1+filename2+"output.txt";
  string equi1command = "java -jar " + RABITPATH + "RABIT.jar " +  outputfile+"_0.ba " + outputfile+"_1.ba  > " + outputfile+"_3.txt ";
  //string equi1command = "java -jar " + RABITPATH + "RABIT.jar " +  outputfile+"_0.ba " + outputfile+"_1.ba";
  system(equi1command.c_str());

  ifstream inFile;
  inFile.open(outputfile+"_3.txt");
  string x;
  inFile >> x;
  //string removeFileCommand = "rm " + filename1 + ".ba " + filename2 + ".ba " + filename1+filename2+"output.txt";
  string removeFileCommand = "rm " + outputfile+"_0.ba " + outputfile+"_1.ba " + outputfile+"_3.tx";
  //cout << x << endl;
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
