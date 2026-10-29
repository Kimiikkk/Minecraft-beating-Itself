#include "config.hpp"
#include "simulator.hpp"
int main(int argc,char**argv){Config c=parseConfig(argc,argv);Simulator s(c);s.run();return 0;}
