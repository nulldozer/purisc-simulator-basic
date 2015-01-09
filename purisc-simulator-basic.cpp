#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#define VERBOSE 1

using namespace std;


class Simulation {
        private:
                int limit;
                vector<int> m;
                
        public:
                Simulation(vector<int> memory, int execLimit) 
                        {m=memory;limit=execLimit;};
                void run();
};

void Simulation::run() {

cout << "simulator's mem:" << endl;
int disp_address = 0;
for(vector<int>::iterator vi = m.begin(); vi != m.end(); vi++) {
    cout << disp_address << "\t" <<  *vi << endl;
    disp_address++;
}

        //loop through instructions, count cycles w/ c
        for(int pc=0, c=0; pc < m.size() && c < limit; c++) 
        {
                cout << "pc:" << pc << endl;
                //readability
                int &a = m[pc+0], &b = m[pc+1], &c=m[pc+2];
                cout << "a:" << a << "\tb:" << b << "\tc:" << c << endl;
                cout << "m[a]:" << m[a] << "\tm[b]:" << m[b] << "\tm[c]:" 
                        << m[c] << endl;
                
                //subleq
                if( (m[b]=m[b]-m[a]) <= 0 ) pc = c;
                else pc += 3;
        }
}

//returns memory size. allocates and populates memory vector
vector<int>
parseMemory(char * fname);
vector<int>
parseMemory(char * fname1, char * fname2);

int 
main(int argc, char* argv[]) 
{
        //memory
        vector<int> m;
        
        int execLimit = 1024;
        //no args
        if(argc == 1) {
                fprintf(stderr, "MOAR ARGS PLZ\n");
        //one file
        } else if(argc == 2) {
                m = parseMemory(argv[1]);
        //two files
        } else if(argc == 3) {
                if(argv[2][0] == '-' && argv[2][1] == 'l')
                        fprintf(stderr, "EXEC LIMIT PLX\n");
                else
                        m = parseMemory(argv[1], argv[2]);
        //one file and a limit
        } else if(argc == 4) {
                if(argv[2][0] == '-' && argv[2][1] == 'l') {
                        string sEL = string(argv[3]);
                        execLimit = stoi(sEL);
                        m = parseMemory(argv[1]);
                } else {
                        fprintf(stderr, "UR ARGS WTF\n");
                }
        //two files and a limit
        } else if(argc == 5) {
                if(argv[3][0] == '-' && argv[3][1] == 'l') {
                        string sEL = string(argv[4]);
                        execLimit = stoi(sEL);
                        m = parseMemory(argv[1], argv[2]);
                } else {
                        fprintf(stderr, "FUCK\n");
                }
        }

        Simulation sim(m, execLimit);
        sim.run();
        
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










































