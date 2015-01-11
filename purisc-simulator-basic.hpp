#include <vector>
#include <string>

using namespace std;

/* for both files */
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



/* for purisc-simulator-basic.cpp */
class Simulation {
        private:
                vector<int> m;
                int pc, a, b, c, count;
                PSBArg args;
        public:
                Simulation(vector<int> memory, PSBArg args);
                bool next();
                string instData();
                string instWrite();
                string instWrite(int * addresses, int length);
                
                int getPC();
                int getA();
                int getB();
                int getC();
                int getDA();
                int getDB();
                int getDC();
};

vector<int>
parseMemory(char * fname);

vector<int>
parseMemory(char * fname1, char * fname2);
