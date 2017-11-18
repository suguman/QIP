
#include "BA.h"
#include "DSComparator.h"
#include "Transition.h"
#include "rabitUtils.h"
#include "rwUtils.h"
#include "wBA.h"
#include "wTransition.h"

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

  //cout << df << filename1 << filename2 << endl;

  wBA* waut1 = readWBA(filename1);
  wBA* waut2 = readWBA(filename2);

  //waut1->printAll();
  //waut2->printAll();

  BA* aut1 = waut1->augmentWtLabel();
  BA* aut2 = waut2->augmentWt();
  //aut1->printAll();
  //aut2->printAll();
  
  //aut1->printAll();
  //aut2->printAll();
  
  BA* autprod = sameAlphaProd(aut2, aut1);
  //autprod->printAll();
  //autprod->printAlpha();

  BA* dstest = makeDSComparator(autprod->getAlpha(), df);
  //dstest->printAll();
  //dstest->printAlpha();
  
  BA* interproject = intersectSelAlpha(autprod, dstest);
  //interproject->printAll();

  projectOutWt(aut1);
  //aut1->printAll();

  //string outputfile = "myfile";
  bool areEqual = checkEqui(aut1, interproject, outputfile);
  cout << areEqual << endl;
  
  
return 0;
}
