#ifndef ADAWEAKNESSES_H
#define ADAWEAKNESSES_H

#include <cstdio>
#include <iostream>
#include <fstream> 
#include <streambuf>

class AdaWeaknesses
{
  public:

  //constructor (needs nothing)
  AdaWeaknesses();

  //weaknesses
  void checkForWeakness1(std::ofstream& mystream);
  void checkForWeakness2(std::ofstream& mystream);
  void checkForWeakness3(std::ofstream& mystream);
  void checkForWeakness4(std::ofstream& mystream);
  void checkForWeakness5(std::ofstream& mystream);
  void checkForWeakness6(std::ofstream& mystream);
  void checkForWeakness7(std::ofstream& mystream);
  void checkForWeakness8(std::ofstream& mystream);
  void checkForWeakness9(std::ofstream& mystream);
  void checkForWeakness10(std::ofstream& mystream);
};

#endif
