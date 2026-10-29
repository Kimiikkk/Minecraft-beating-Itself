#include "config.hpp"
#include <string>
#include <iostream>
Config parseConfig(int argc,char**argv){
    Config c;
    for(int i=1;i<argc;i++){
        std::string a=argv[i];
        auto val=[&](){return i+1<argc?std::string(argv[++i]):std::string();};
        if(a=="--seed") c.seed=std::stoll(val());
        else if(a=="--replay") c.replay=val();
        else if(a=="--max-events") c.maxEvents=std::stoull(val());
        else if(a=="--max-years") c.maxYears=std::stod(val());
        else if(a=="--quiet") c.verbose=false;
        else if(a=="--help") std::cout<<"--seed N --replay FILE --max-events N --max-years N --quiet\n";
    }
    return c;
}
