/*
 * rabitUtils.h
 *
 * Created on: November 6, 2017
 * Author: Suguman Bansal
 */


#ifndef RABITUTILS_H
#define RABITUTILS_H

#include "common.h"
#include "wBA.h"

using namespace std;

//BA* reduce(string filename);

BA* reduce(BA* aut);

int checkEqui(BA* aut1, BA* aut2, string outputfile);
#endif
