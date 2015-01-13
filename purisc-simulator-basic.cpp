#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <getopt.h>
#include <exception>
#include "purisc-simulator-basic.hpp"


using namespace std;

int 
main(int argc, char** argv) 
{
        PSBArg args = toPSBArg(argc, argv);
        vector<int> m;
        try {
            if(args.oneFile)
                m = parseMemory(args.fileName[0]);
            else
                m = parseMemory(args.fileName[0], args.fileName[1], 
                        args.dataMemOffset);
        } catch(int e) {
            if(e == 0)
                cerr << "Error reading memory file" << endl;
            else if(e == 1)
                cerr << "Data memory offset too small" << endl;
            exit(EXIT_FAILURE);
        } 
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
    args.dataMemOffset = -1;
    int argCount = 0;
    int c;


    while (1)
    {
        static struct option long_options[] =
        {
            {"limit",           required_argument,  0, 'l'},
            {"data-offset",     required_argument,  0, 'o'},
            {"show-pc",         no_argument,        0, 'p'},
            {"show-decoded",    no_argument,        0, 'd'},
            {"show-resolved",   no_argument,        0, 'r'},
            {"show-writes",     no_argument,        0, 'w'},
            {"writes-location", required_argument,  0, 'g'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "l:o:pdrwg:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
        break;

        switch (c)
        {
            case 'l':
                args.execLimit = atoi(optarg);
                argCount+=2;
                break;
                
            case 'o':
                args.dataMemOffset = atoi(optarg);
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
    } else if (argc-argCount == 3 && args.dataMemOffset < 0) {
        cerr << "Two file operation: specify data memory offset with -o or --data-offset" << endl;
        exit(EXIT_FAILURE);
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
    
    string line;
    ifstream file;
    file.open(fname);
    if(file.fail()) throw(0);
    
    while ( getline(file, line) ) {
        if(!file.eof()){
            try {
                memory.push_back( stoi(line) );
            } catch (int se) {
                cerr << "Machine code parsing error" << endl;
            }
        }
    }
    file.close();
    return memory;
}

vector<int>
parseMemory(char * fname1, char * fname2, int dataMemOffset)
{
    //parse the first file
    vector<int> progMem = parseMemory(fname1);
    //prepare the zero pad
    int padLength = dataMemOffset - progMem.size();
    if(padLength < 0) throw(1);
    vector<int> zeroPad;
    zeroPad.assign(padLength, 0);
    //parse the second file
    vector<int> dataMem = parseMemory(fname2);
    
    //stitch everything together
    vector<int> memory;
    memory.reserve(dataMemOffset + dataMem.size());
    memory.insert( memory.end(), progMem.begin(), progMem.end() );
    memory.insert( memory.end(), zeroPad.begin(), zeroPad.end() );
    memory.insert( memory.end(), dataMem.begin(), dataMem.end() );
    return memory;
}

