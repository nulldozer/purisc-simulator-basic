#include <vector>

using namespace std;

class Simulation {
        private:
                vector<int> m;
                int pc, a, b, c, count, execLimit;
        public:
                Simulation(vector<int> memory, int limit);
                bool next();
                
                int getPC();
                int getA();
                int getB();
                int getC();
                int getDA();
                int getDB();
                int getDC();
};
