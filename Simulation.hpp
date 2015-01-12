#include <string>
#include <vector>

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

class Simulation {
        private:
                vector<int> m;
                int pc, a, b, c, count, execLimit;
                PSBArg args;
        public:
                Simulation(vector<int> memory, PSBArg args);
                bool next();
                
                int getPC();
                int getA();
                int getB();
                int getC();
                int getDA();
                int getDB();
                int getDC();
};
