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
**-l** LIMIT **--limit LIMIT**
&nbsp;&nbsp;&nbsp;&nbsp;stop execution after LIMIT cycles
**-o**  **--data-offset**
&nbsp;&nbsp;&nbsp;&nbsp;if two memory files are given, this is the location where the second file's values are loaded into the processor's memory
**-p**  **--show-pc**
&nbsp;&nbsp;&nbsp;&nbsp;
**-d**  **--show-decoded**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;show each operand of the instruction (a, b, c)
**-r**  **--show-resolved**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;show the resolved pointers within the instruction (mem[a], mem[b], mem[c])
**-w**  **--show-writes**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;show what has been written back
**-g**  **--writes-location**
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;show only what has been written back to this register



