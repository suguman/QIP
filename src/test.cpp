
#include "BA.h"
#include "DSComparator.h"
#include "memory.h"
#include "timers.h"
#include "Transition.h"
#include "rabitUtils.h"
#include "rwUtils.h"
#include "wBA.h"
#include "wTransition.h"

#include <chrono>

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
  ofs << outputStr; 
  ofs.close();
  
  auto startTime = chrono::high_resolution_clock::now();
  //time_t startTime;
  //time(&startTime);
  //cout << startTime << endl;
  //clock_t beginClock = clock();
  //cout << beginClock << endl;

  //cout << &wallstart << endl;
  //double startTime = cpuTimeTotal();
  
  wBA* waut1 = readWBA(filename1);
  wBA* waut2 = readWBA(filename2);
 
  //cout << "Mem after reading inputs " << getPhysicalMem() << endl;
  BA* aut1 = waut1->augmentWtLabel();
  BA* aut2 = waut2->augmentWt();

  //Free both wBA

  cout << "Mem after augment " << getPhysicalMem() << endl;

  //cout << aut1->getTransNum() << endl;
  //cout << aut2->getTransNum() << endl;
  
  BA* autprod = sameAlphaProd(aut2, aut1);
  projectOutWt(aut1);
  //Free aut2

  cout << "Mem Before making comparator " << getPhysicalMem() << endl;
  cout << "Time before comaprator " << cpuTimeTotal() << endl;

  BA* dstest = makeDSComparator(autprod->getAlpha(), df, outputfileroot);
 
  cout << "Mem after making comparator " << getPhysicalMem() << endl;

  BA* interproject = intersectSelAlpha(autprod, dstest);
  //interproject->printAll();

  cout << "Mem after intersectproject " << getPhysicalMem() << endl;
  // Free dstest, autprod

  //projectOutWt(aut1);
  //aut1->printAll();

  cout << "Before rabit " << getPhysicalMem() << endl;
  //double rabitStart = cpuTimeTotal();
  
  auto rabitStart = chrono::high_resolution_clock::now();
  //time_t rabitStart;
  //time(&rabitStart);
  //cout << "Starting rabit "<< rabitStart << endl;
  int areEqual = checkEqui(aut1, interproject, outputfile);

  //double rabitEnd = cpuTimeTotal();
  auto rabitEnd = chrono::high_resolution_clock::now();
  //time_t rabitEnd;
  //time(&rabitEnd);
  //cout << "Time end " << rabitEnd << endl;
  cout << "Mem end " << getPhysicalMem() << endl;
  
  //time_t wallend;
  //time(&wallend);
  //cout << wallend << endl;
  //cout << "Wall time total " << rabitEnd - startTime << endl;
  //cout << "Rabit time total " << rabitEnd - rabitStart << endl;
  
  //clock_t endclock = clock();

  //cout << "Clock time " << endclock-beginclock << endl;
  //Change from here
  int numStatesA1 = aut1->getStateNum();
  int numStatesA2 = interproject->getStateNum();
  int numTransA1 = aut1->getTransNum();
  int numTransA2 = interproject->getTransNum();
  //TIll here

  //Free aut1 and interproject

  //double rabitEnd = cpuTimeTotal();
  
  //double endTime = cpuTimeTotal();
  
  //ofstream ofs;

  double tfull = (chrono::duration_cast<chrono::milliseconds>(rabitEnd - startTime).count())/1000.0;
  double trabit = (chrono::duration_cast<chrono::milliseconds>(rabitEnd - rabitStart).count())/1000.0;

  cout << "Wall time " << tfull << endl;
  cout << "Rabit time " << trabit << endl;

  ofs.open (outputfile+".txt", ofstream::out | ofstream::app);
  outputStr = "Qip " + to_string(areEqual) + " " + to_string(tfull) + " " + to_string(trabit) + " " + to_string(numStatesA1) + " " + to_string(numStatesA2) + " " + to_string(numTransA1) + " " + to_string(numTransA2) + "\n";
  ofs << outputStr; 
  ofs.close();
  //cout << areEqual <<" " <<  (endTime-startTime) <<  " " << (rabitEnd - rabitStart) << endl;
  
  //return areEqual;
  return 0;
}


