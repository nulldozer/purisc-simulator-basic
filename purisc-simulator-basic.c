#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_MEMORY_ADDRESS 0x011FFF
void print_usage(char * a){
    fprintf(stderr, "USAGE:\n\t%s [-l LIMIT] fname\n", a);
}

int main(int argc, char ** argv){
    char *fname;
    int i; 
    long int start=0, limit=32;
    
    if(argc == 1) {
        print_usage(argv[0]);
        return(1);
    } else {
        for(i=1; i < argc; i++) {
            if(argv[i][0] == '-') {
                if(i+1 < argc) {
                    if(argv[i][1] == 'l') {
                        limit=strtol(argv[++i], NULL, 10);
                    } else if(argv[i][1] == 's') {
                        start=strtol(argv[++i], NULL, 10);
                    } else {
                        print_usage(argv[0]);
                        return 1; 
                    }
                } else {
                    print_usage(argv[0]);
                    return 1;
                }
            } else {
                fname = argv[i];
            }
        }
    }

    //load code into memory
    FILE *fp = fopen(fname, "r");
    int readvalue, pc=start;
    int * m = (int*) malloc(MAX_MEMORY_ADDRESS*sizeof(int));
    memset(m,0,MAX_MEMORY_ADDRESS+1);
    for(i=0; fscanf(fp, "%d", &readvalue) > 0; i++) {
        m[i]=readvalue;
    }

    //run simulation
    printf("        pc        b   =    b    -   a\n");
    for(i=0;i<limit;i++){
        //print logic
        printf("0x%08x %8d %8d %8d",
            pc,m[m[pc+1]]-m[m[pc+0]],m[m[pc+1]],m[m[pc+0]]);
        if(m[m[pc+1]]-m[m[pc+0]] <= 0)
            printf("   |   branch to 0x%08x (%d)\n", m[pc+2],m[pc+2]);
        else 
            printf("\n");
        //actual logic
        //*b=*b-*a
        m[m[pc+1]] = m[m[pc+1]]-m[m[pc+0]];
        //pc=c if *b <= 0
        if(m[m[pc+1]] <= 0) {
            pc=m[pc+2];
        } else {
            pc=pc+3;
        }
    }

    //clean up
    fclose(fp);
    free(m);

    return 0;
}
