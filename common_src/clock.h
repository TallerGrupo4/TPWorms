#include <functional>
#include <chrono>
#include <thread>
#include <iostream>

#include "yamlReader.h"

#ifndef CLOCK_H
#define CLOCK_H

class Clock {
    int rate; // e.g. 16 milisec
    std::function<void(int)> func;
    bool& keep_ticking; 
    public:
    // Framerate is for example 60 fps, so frame duration is 1/60 seconds , we convert them to miliseconds
    Clock(std::function<void(int)> func, float frameDuration, bool& keep_ticking): func(func), keep_ticking(keep_ticking){
        rate = std::round (frameDuration * 1000);
    }
    
    ~Clock() {}

    void tick() {
        int iter = 1;
        auto t1 = std::chrono::high_resolution_clock::now(); // 17:25:02
        while (keep_ticking){
            func(iter);
            iter = 0;
            auto t2 = std::chrono::high_resolution_clock::now(); // 17:25:03
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();;
            int rest = rate - diff;
            if (rest < 0) {
                int behind = (-1) * rest;
                rest = rate - behind % rate;
                int lost = behind + rest;
                t1 += std::chrono::milliseconds(lost);
                iter += lost / rate;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(rest));
            t1 += std::chrono::milliseconds(rate);
            iter++;

        }

    }

    void stop_ticking(){
        keep_ticking = false;
    }
};

#endif // CLOCK_H
