#include <iostream>
#include <vector>
#include <stdlib.h>
#include <getopt.h>
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

        Simulation * sim = new Simulation(m, args.execLimit);
        
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

PSBArg
toPSBArg (int argc, char **argv)
{
    //default values
    PSBArg args;
    args.instAddr = false;
    args.instDecoded = false;
    args.instData = false;
    args.instWrite = false;
    args.instrWriteRegister = -1;
    args.execLimit = -1;
    int argCount = 0;
    int c;


    while (1)
    {
        static struct option long_options[] =
        {
            {"limit",           required_argument,  0, 'l'},
            {"show-pc",         no_argument,        0, 'p'},
            {"show-decoded",    no_argument,        0, 'd'},
            {"show-resolved",   no_argument,        0, 'r'},
            {"show-writes",     no_argument,        0, 'w'},
            {"writes-location", required_argument,  0, 'g'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "f:l:pdrwg:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
        break;

        switch (c)
        {
            case 'l':
                args.execLimit = atoi(optarg);
                argCount+=2;
                break;

            case 'p':
                args.instAddr = true;
                argCount++;
                break;

            case 'd':
                args.instDecoded = true;
                argCount++;
                break;

            case 'r':
                args.instData = true;
                argCount++;
                break;

            case 'w':
                args.instWrite = true;
                argCount++;
                break;
            case 'g':
                args.instrWriteRegister = atoi(optarg);
                argCount+=2;
                break;
            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
            exit(EXIT_FAILURE);
        }
    }
    
    
    if(argc-argCount == 2) {
        args.oneFile = true;
        args.fileName[0] = argv[argc-1];
    } else if (argc-argCount == 3){
        args.oneFile = false;
        args.fileName[0] = argv[argc-2];
        args.fileName[1] = argv[argc-1];
    } else {
        cerr << "Could not interpret file name(s) properly" << endl;
        exit(EXIT_FAILURE);
    }
    
    return args;
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
        if(pmFile == NULL || dmFile == NULL) {
            fprintf(stderr, "Couldn't open file\n");
            abort();
        }
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

