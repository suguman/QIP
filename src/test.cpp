
#include "BA.h"
#include "DSComparator.h"
#include "timers.h"
#include "Transition.h"
#include "rabitUtils.h"
#include "rwUtils.h"
#include "wBA.h"
#include "wTransition.h"

#include <time.h>

int main (int argc, char** argv){
  //0-th argument is ./quip
  //1-st argument in discount-factor
  //2-nd argument is input filename1.txt
  //3-rd argument is input filename2.txt
  //4-th argument is outputfilename
  //5-th argument is iterNo

  
  int df = stoi(argv[1]);
  string filename1 = argv[2];
  string filename2 = argv[3];
  string outputfile = argv[4];
  string outputfileroot = outputfile.substr(8);
  cout << outputfileroot << endl;
  //int iterno = stoi(argv[5]);
  
  ofstream ofs;
  ofs.open (outputfile+".txt", ofstream::out | ofstream::app);
  string outputStr = "N\n";
  //ofs << outputStr; 
  ofs.close();
  
 
  double startTime = cpuTimeTotal();
  
  wBA* waut1 = readWBA(filename1);
  wBA* waut2 = readWBA(filename2);
 

  BA* aut1 = waut1->augmentWtLabel();
  BA* aut2 = waut2->augmentWt();

  
  
  BA* autprod = sameAlphaProd(aut2, aut1);
  
  
  BA* dstest = makeDSComparator(autprod->getAlpha(), df, outputfileroot);
 
  BA* interproject = intersectSelAlpha(autprod, dstest);
   
  projectOutWt(aut1);
  //aut1->printAll();
  
  double rabitStart = cpuTimeTotal();
  
  int areEqual = checkEqui(aut1, interproject, outputfile);
  
  double rabitEnd = cpuTimeTotal();
  
  double endTime = cpuTimeTotal();
  
  //ofstream ofs;
  ofs.open (outputfile+".txt", ofstream::out | ofstream::app);
  outputStr = to_string(areEqual) + " " + to_string(endTime-startTime) + " " + to_string(rabitEnd - rabitStart) + "\n";
  //ofs << outputStr; 
  ofs.close();
  //cout << areEqual <<" " <<  (endTime-startTime) <<  " " << (rabitEnd - rabitStart) << endl;
  
  //return areEqual;
  return 0;
}


