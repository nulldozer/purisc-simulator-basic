#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "purisc-simulator-basic.hpp"

/* Flag set by ‘--verbose’. */
static int verbose_flag;

/*
options:
    --pc            show pc
    --decoded       show decoded instructions
    --resolved      show resolved pointers a and b
    --show-writes   show result (value written)
    --write-regs    show only writes to register(s) #
*/

PSBArg
toPSBArg (int argc, char **argv)
{
    
    PSBArg args;
    args.instAddr = 1;
    args.instDecoded = 1;
    args.instData = 1;
    args.instWrite = 1;
    args.instrWriteRegister = -1;
    args.oneFile = true;
    args.fileName[0] = "input.machine";
    int c;

    while (1)
    {   
        static struct option long_options[] =
        {
            /* These options set a flag. */
            {"verbose", no_argument,       &verbose_flag, 1},
            {"brief",   no_argument,       &verbose_flag, 0},
            /* These options don’t set a flag.
            We distinguish them by their indices. */
            {"add",     no_argument,       0, 'a'},
            {"append",  no_argument,       0, 'b'},
            {"delete",  required_argument, 0, 'd'},
            {"create",  required_argument, 0, 'c'},
            {"file",    required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "abc:d:f:",
        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
        break;

        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'a':
                puts ("option -a\n");
                break;

            case 'b':
                puts ("option -b\n");
                break;

            case 'c':
                printf ("option -c with value '%s'\n", optarg);
                break;

            case 'd':
                printf ("option -d with value '%s'\n", optarg);
                break;

            case 'f':
                printf ("option -f with value '%s'\n", optarg);
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
            abort ();
        }
    }
    return args;
}

