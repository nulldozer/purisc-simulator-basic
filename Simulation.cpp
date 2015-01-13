#include "Simulation.hpp"
//TEMP
#include <iostream>

using namespace std;
Simulation::Simulation(vector<int> memory, int limit)
{
    pc=0; 
    count=0;
    m=memory;
    execLimit=limit;
}

bool
Simulation::next() 
{
    bool success;
    if(pc < m.size() && (count < execLimit || execLimit < 0)){
        a = m[pc+0];
        b = m[pc+1];
        c = m[pc+2];
        //subleq
        if( (m[b]=m[b]-m[a]) <= 0 ) pc = c;
        else pc += 3;
        success = true;
    } else {
        success = false;
    }
    count++;
    return success;
}
int Simulation::getPC() { return pc; }
int Simulation::getA() { return a; }
int Simulation::getB() { return b; }
int Simulation::getC() { return c; }
int Simulation::getDA(){ return m[a]; }
int Simulation::getDB(){ return m[b]; }
int Simulation::getDC(){ return m[c]; }

