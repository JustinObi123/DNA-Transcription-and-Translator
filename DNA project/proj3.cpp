//Title: proj3.h
//Author: Jeremy Dixon
//Date: 3/14/2023
//Description: This is part of the Transcription and Translation Project in CMSC 202 @ UMBC

#include "Sequencer.h"
#include <iostream>
using namespace std;

//This allows data to be passed when calling the executable
//For example, ./proj3 proj3_data1.txt would pass proj3_data1.txt as argv[1] below
int main (int argc, char* argv[]) {
  if (argc < 2)
    {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj3 proj3_data1.txt" << endl;
      cout << "File 1 should be a file with one or more DNA strands" << endl;
    }
  else
    {
      cout << endl << "***Transcription and Translation***" << endl << endl;
      Sequencer D = Sequencer(argv[1]); //Passes the file name into the Sequencer constructor
      D.StartSequencing();//Starts the sequencer
    }
  return 0;
}
