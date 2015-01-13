# purisc-simulator-basic
Simulates the output and memory contents of a purisc processor, omitting the details of the pipeline (like data hazards, forwarding, mispredicted branches and flushing, etc...)

### Compiling
    > make

### Usage
    ./simulator_basic [options] file1 [file2]
        
For one-file operation, file must be a list of values in memory 
delimited by whitespace(no addresses or other symbols). One-file 
operation is simpler and more reliable, and therefore recommended.

For two-file operation, file1 is the program memory (program assumes 
memory starts at address zero) and file2 is the data memory. Data memory
must include addresses since the cpu doesn't know where it starts. 
        
### Options
    -l LIMIT    --limit LIMIT
        stop execution after LIMIT cycles
    -o OFFSET   --data-offset OFFSET
        if two memory files are given, this is the location where the second file's values are loaded into the processor's memory
    -p  --show-pc

    -d  --show-decoded
        show each operand of the instruction (a, b, c)
    -r  --show-resolved
        show the resolved pointers within the instruction (mem[a], mem[b], mem[c])
    -w  --show-writes
        show what has been written back
    -g  --writes-location
        show only what has been written back to this register



