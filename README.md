# purisc-simulator-basic
Simulates the output and memory contents of a purisc processor, omitting the details of the pipeline (like data hazards, forwarding, mispredicted branches and flushing, etc...)

### Compiling
    > make

### Usage
    ./simulator_basic [options] file
        
 
### Options
    -l LIMIT
        stop execution after LIMIT cycles
    -s START
        start executing code at address START (decimal)

