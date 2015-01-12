#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "Simulation.hpp"

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
    args.oneFile = true;
    args.fileName[0] = "input.machine";
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
            abort ();
        }
    }
    
    
    if(argc-argCount == 2) {
        args.oneFile = true;
        args.fileName[0] = argv[argc-1];
    } else {
        args.oneFile = false;
        args.fileName[0] = argv[argc-2];
        args.fileName[1] = argv[argc-1];
    }
    
    printf("oneFile = %d\n", args.oneFile);
    
    return args;
}

