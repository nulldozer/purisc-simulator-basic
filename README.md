# purisc-simulator-basic
Simulates the output and memory contents of a purisc processor, omitting the details of the pipeline (like data hazards, forwarding, mispredicted branches and flushing, etc...)

This is shit code, but it works.

## TO COMPILE:
        > make

## USAGE:
        ./simulator_basic file1 [file2]
        
For one-file operation, file must be a list of values in memory 
delimited by whitespace(no addresses or other symbols). One-file 
operation is simpler and more reliable, and therefore recommended.

For two-file operation, file1 is the program memory (program assumes 
memory starts at address zero) and file2 is the data memory. Data memory
must include addresses since the cpu doesn't know where it starts. 
        
### OPTIONS:
    -l LIMIT
        stop the execution after LIMIT cycles


