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
//const char* RABITPATH = "../../Tools/RABIT/";

void reduce(string filename){
  //const char* command = "java -Xss1G -Xms1G -jar ../../Tools/RABIT/Reduce.jar test1.ba 30";
  string reduceCommand = "java -Xss1G -Xms1G -jar " + RABITPATH + "Reduce.jar " + filename + ".ba 30";
  system(reduceCommand.c_str());
  //BA* reducedBA = readBA("reduced_30_"+filename + ".ba");
  string removeFile = "rm " + filename + ".ba " + "reduced_30_" + filename + ".ba";
  //system(removeFile.c_str());
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
