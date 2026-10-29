#include "rng.hpp"
#include <cmath>
double RNG::u(){return std::generate_canonical<double,64>(e);}
double RNG::uniform(double a,double b){return a+(b-a)*u();}
bool RNG::chance(double p){return u()<p;}
std::int64_t RNG::integer(std::int64_t a,std::int64_t b){std::uniform_int_distribution<std::int64_t>d(a,b);return d(e);}
double RNG::exponential(double mean){return -mean*std::log(std::max(1e-15,u()));}
double RNG::lognormal(double median,double sigma){std::lognormal_distribution<double>d(std::log(median),sigma);return d(e);}
