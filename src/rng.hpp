#pragma once
#include <cstdint>
#include <random>
class RNG {
    std::mt19937_64 e;
public:
    explicit RNG(std::uint64_t seed):e(seed){}
    double u();
    double uniform(double a,double b);
    bool chance(double p);
    std::int64_t integer(std::int64_t a,std::int64_t b);
    double exponential(double mean);
    double lognormal(double median,double sigma);
    std::uint64_t raw(){return e();}
};
