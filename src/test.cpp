
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
  //2-nd argument is filename1.txt
  //3-rd argument is filename2.txt
  
  int df = stoi(argv[1]);
  string filename1 = argv[2];
  string filename2 = argv[3];

  //cout << df << filename1 << filename2 << endl;

  wBA* waut1 = readWBA(filename1);
  wBA* waut2 = readWBA(filename2);

  waut1->printAll();
  waut2->printAll();

  BA* aut1 = waut1->augmentWtLabel();
  BA* aut2 = waut2->augmentWt();

  aut1->printAll();
  aut2->printAll();
  
  BA* autprod = sameAlphaProd(aut2, aut1);
  autprod->printAll();

  //TODO : Extract weight from autprod
  int ar[] = {0, 1, -1};
  BA* dstest = makeDS(df, ar, 3);
  

  BA* interproject = intersectSelAlpha(autprod, dstest);
  interproject->printAll();

  projectOutWt(aut1);
  aut1->printAll();

  string file1 = "file1";
  string file2  = "file2";
  bool areEqual = checkEqui(aut1, interproject, file1, file2);
  cout << areEqual << endl;
  //aut1->writeToFile("file1");
  //inter->writeToFile("file2");
  
  /*

  wBA* readAut = readWBA("textfile.txt");
  //cout << readAut.getTrans() << endl; 
  //readAut.printTrans();
  readAut->printAll();

  BA* aut = readAut->augmentWt();
  aut->printAll();

  BA* autnew = readAut->augmentWtLabel();
  autnew->printAll();

  BA* autprod = sameAlphaProd(aut, autnew);
  //autprod->printAll();

  //BA* autba = readBA("testfile2.txt");
  //autba->printAll();

  
  //dstest->printAll();
  //dstest.printAll();

  BA* inter = intersectSelAlpha(autprod, dstest);
  //inter->printAll();

  autnew->printAlpha();
  projectOutWt(autnew);

  autnew->printAlpha();
  autnew->printTrans();

  //reduce("testBA");

  autnew->writeToFile("test");
  BA* autba2 = readBA("test.ba");
  autba2->printAll();
  
  string filename = "DS";
  dstest->writeDSToFile(filename);
  dstest->printFinal();
  reduce (filename);
  BA* dsreduced = readDS("reduced_30_"+filename+".ba");
  dsreduced->printAll();

  */
return 0;
}
