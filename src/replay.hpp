#pragma once
#include "events.hpp"
#include "world.hpp"
#include "entities.hpp"
#include <fstream>
class Replay {
    std::ofstream f;
    static std::string esc(const std::string&);
public:
    explicit Replay(const std::string&p):f(p){}
    void header(std::int64_t seed,const World&w);
    void write(const Event&e,const World&w,const Entities&es);
};
