#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "purisc-simulator-basic.hpp"

using namespace std;
/*
options:
    --pc            show pc
    --decoded       show decoded instructions
    --resolved      show resolved pointers a and b
    --show-writes   show result (value written)
    --write-regs    show only writes to register(s) #
*/
Simulation::Simulation(vector<int> memory, PSBArg opts)
{
    int pc=0; 
    int count=0;
    m=memory;
    args = opts;
}
bool
Simulation::next() 
{
    bool success;
    if(pc < m.size() && count < args.execLimit){
        a = m[pc+0]; 
        b = m[pc+1];
        c = m[pc+2];
        //subleq
        if( (m[b]=m[b]-m[a]) <= 0 ) pc = c;
        else pc += 3;
        success = true;
    } else {
        success = false;
    }
    count++;
    return success;
}
int Simulation::getPC() { return pc; }
int Simulation::getA() { return a; }
int Simulation::getB() { return b; }
int Simulation::getC() { return c; }
int Simulation::getDA(){ return m[a]; }
int Simulation::getDB(){ return m[b]; }
int Simulation::getDC(){ return m[c]; }

// TODO: this
string 
instWrite(int * addresses, int length)
{
    return "not implemented";
}

int 
main(int argc, char** argv) 
{
/*
        //memory
        vector<int> m;
        
        int execLimit = 1024;
        //no args
        if(argc == 1) {
                fprintf(stderr, "MOAR ARGS PLZ\n");
        //one file
        } else if(argc == 2) {
                m = parseMemory(argv[1]);
        //two files
        } else if(argc == 3) {
                if(argv[2][0] == '-' && argv[2][1] == 'l')
                        fprintf(stderr, "EXEC LIMIT PLX\n");
                else
                        m = parseMemory(argv[1], argv[2]);
        //one file and a limit
        } else if(argc == 4) {
                if(argv[2][0] == '-' && argv[2][1] == 'l') {
                        string sEL = string(argv[3]);
                        execLimit = stoi(sEL);
                        m = parseMemory(argv[1]);
                } else {
                        fprintf(stderr, "UR ARGS WTF\n");
                }
        //two files and a limit
        } else if(argc == 5) {
                if(argv[3][0] == '-' && argv[3][1] == 'l') {
                        string sEL = string(argv[4]);
                        execLimit = stoi(sEL);
                        m = parseMemory(argv[1], argv[2]);
                } else {
                        fprintf(stderr, "FUCK\n");
                }
        }
*/
        
        PSBArg args = toPSBArg(argc, argv);
        vector<int> m;
        if(args.oneFile)
            m = parseMemory(args.fileName[0]);
        else
            m = parseMemory(args.fileName[0], args.fileName[1]);

        Simulation * sim = new Simulation(m, args);
        
        do {
            if(args.instAddr) cout << sim->getPC() << endl;
            if(args.instDecoded) cout << "a:" << sim->getA()
                                    << "\tb:" << sim->getB()
                                    << "\tc:" << sim->getC() << endl;
            if(args.instData) cout << "m[a]:" << sim->getDA() 
                                << "\tm[b]:" << sim->getDB()
                                << "\tm[c]:" << sim->getDC() << endl;
            if(args.instWrite) cout << "addr:" << sim->getB()
                                    << "data:" << sim->getDB() << endl;
        } while ( sim->next() );
        
        return 0;
}

vector<int>
parseMemory(char * fname)
{
        vector<int> memory;
        FILE * txtFile = fopen(fname,"r");
        int valueRead;
        for(int i = 0; fscanf(txtFile,"%i",&valueRead) != EOF; i++)
                memory.push_back(valueRead);
        fclose(txtFile);
        
        return memory;
}

vector<int>
parseMemory(char * fname1, char * fname2)
{
        vector<int> memory;
        FILE * pmFile = fopen(fname1,"r");
        FILE * dmFile = fopen(fname2,"r");
        int valueRead;
        
        //read in the first address of data memory
        fscanf(dmFile,"%i",&valueRead);
        int dataMemStart = valueRead;
        
        //populate program memory
        for(int i = 0; fscanf(pmFile,"%i",&valueRead) != EOF; i++)
                memory.push_back(valueRead);
        //offset the data mem
        for(int i = memory.size(); i < dataMemStart; i++)
                memory.push_back(0);
        //populate data memory
        bool isAddress = true;
        for(int i = dataMemStart; fscanf(dmFile,"%i",&valueRead) != EOF; i++) {
                if(isAddress) memory.push_back(valueRead);
                isAddress = !isAddress;
        }
        
        fclose(pmFile);
        fclose(dmFile);
        
        return memory;
}

