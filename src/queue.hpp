#pragma once
#include "events.hpp"
#include <queue>
class EventQueue {
    std::priority_queue<Event,std::vector<Event>,Compare> q;
public:
    void push(Event e){q.push(std::move(e));}
    bool empty()const{return q.empty();}
    Event pop(){auto e=q.top();q.pop();return e;}
    std::size_t size()const{return q.size();}
};
