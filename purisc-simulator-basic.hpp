#include <vector>
#include <string>
#include "Simulation.hpp"

using namespace std;

class readMemoryException: public exception
{
  virtual const char* what() const throw()
  {
    return "";
  }
} myex;

struct PSBArg {
    bool instAddr;
    bool instDecoded;
    bool instData;
    bool instWrite;
    int instrWriteRegister;
    int execLimit;
    bool oneFile;
    char * fileName[2];
    int dataMemOffset;
};

PSBArg 
toPSBArg (int argc, char **argv);

vector<int>
parseMemory(char * fname);

vector<int>
parseMemory(char * fname1, char * fname2, int dataMemOffset);
