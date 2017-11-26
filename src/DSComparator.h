/*
 * DSComparator.h
 *
 * Created on: November 14, 2017
 * Author: Suguman Bansal
 */

#ifndef DSCOMPARATOR_H
#define DSCOMPARATOR_H



#include "common.h"
#include "Transition.h"

using namespace std;



BA* makeDS(int df, int* difList, int len);

BA* makeDSComparator(vector<string>* alphaList, int df, string filename);
  


#endif 
