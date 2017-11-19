
#include "BA.h"
#include "DSComparator.h"
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
  
  int df = stoi(argv[1]);
  string filename1 = argv[2];
  string filename2 = argv[3];
  string outputfile = argv[4];


  time_t startTime;
  time(&startTime);
  
  wBA* waut1 = readWBA(filename1);
  wBA* waut2 = readWBA(filename2);
  //cout << outputfile <<  " " << "Read inputs" << endl;
  //waut1->printAll();
  //waut2->printAll();

  BA* aut1 = waut1->augmentWtLabel();
  BA* aut2 = waut2->augmentWt();

  //cout << outputfile <<  " " << "augmentation " << endl;
  //aut1->printAll();
  //aut2->printAll();
  
  //aut1->printAll();
  //aut2->printAll();
  
  BA* autprod = sameAlphaProd(aut2, aut1);
  //autprod->printAll();
 
  //cout << outputfile <<  " " << "Same prod" << endl;

  //autprod->printAll();
  
  BA* dstest = makeDSComparator(autprod->getAlpha(), df);
  //dstest->printAll();
  //dstest->printAlpha();
  //cout << outputfile <<  " " << "Comparator" << endl;
  
  BA* interproject = intersectSelAlpha(autprod, dstest);
  //interproject->printAll();

  //cout << outputfile <<  " " << "Intersect" << endl;
  
  projectOutWt(aut1);
  //aut1->printAll();

  //cout << outputfile <<  " " << "Project" << endl;
  
  //string outputfile = "myfile";
  time_t rabitStart;
  time(&rabitStart);
  int areEqual = checkEqui(aut1, interproject, outputfile);

  //cout << outputfile <<  " " << "Inclusion testing" << endl;
  time_t rabitEnd;
  time(&rabitEnd);
  //usleep(100000);
  
  time_t endTime;
  time(&endTime);

  ofstream ofs;
  ofs.open (outputfile+".txt", std::ofstream::out | std::ofstream::app);
  string outputStr = to_string(areEqual) + " " + to_string(endTime-startTime) + " " + to_string(rabitEnd - rabitStart) + "\n";
  ofs << outputStr; 
  ofs.close();
  //cout << areEqual <<" " <<  (endTime-startTime) <<  " " << (rabitEnd - rabitStart) << " " << endl;
  
  //return areEqual;
  return 0;
}


