/*
 * rwUtils.h
 *
 * Created on: November 6, 2017
 * Author: Suguman Bansal
 */


#ifndef RWUTILS_H
#define RWUTILS_H

#include "common.h"
#include "wBA.h"


using namespace std;

wBA* readWBA(string filename);

BA* sameAlphaProd(BA* aut1, BA* aut2);

#endif
