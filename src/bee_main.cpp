#include "world/beehive.h"

using namespace world;


int main(int argc, char* argv[]) {
    if(argc < 6){
        std::cout<<"Less number of command line arguments"<<std::endl;
    }else {
        Beehive bh(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        bh.add_bees();
        bh.start_simulation();
    }
    return 0;
}