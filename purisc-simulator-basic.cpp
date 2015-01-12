#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "purisc-simulator-basic.hpp"

using namespace std;

int 
main(int argc, char** argv) 
{
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
        
        delete sim;
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

