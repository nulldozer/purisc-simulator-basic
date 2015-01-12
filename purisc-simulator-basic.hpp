#include <vector>
#include <string>
#include "Simulation.hpp"

using namespace std;

struct PSBArg {
    bool instAddr;
    bool instDecoded;
    bool instData;
    bool instWrite;
    int instrWriteRegister;
    int execLimit;
    bool oneFile;
    char * fileName[2];
};

PSBArg 
toPSBArg (int argc, char **argv);

vector<int>
parseMemory(char * fname);

vector<int>
parseMemory(char * fname1, char * fname2);
