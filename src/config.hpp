#pragma once
#include <cstdint>
#include <string>
struct Config {
    std::int64_t seed = -535646876083114041LL;
    std::string replay = "replay.jsonl";
    std::uint64_t maxEvents = 250000;
    double maxYears = 10e9;
    bool verbose = true;
};
Config parseConfig(int argc,char**argv);
