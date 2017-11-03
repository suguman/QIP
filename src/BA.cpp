//============================================================================
// Name        : BA.cpp
// Author      : Suguman Bansal
// Version     :
// Copyright   : Your copyright notice
// Description : Class for Buchi automata 
//============================================================================

#inlcude <iostream>
#include <string>
#include <vector>
#include "BA.h"

using namespace std;

BA::BA(){
  numStates = 0;
  alphabet = {};
  initial = {};
  final = {};
  transFunc = {};
}

BA::~BA(){
  //TODO
};
