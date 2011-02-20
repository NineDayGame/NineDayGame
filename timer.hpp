#ifndef NDG_TIMER_HPP_
#define NDG_TIMER_HPP_

#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "basetypes.hpp"

class Timer {
public:
    typedef boost::shared_ptr<Timer> ShPtr;
    
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_started();
    bool is_paused();

private:
    int startTicks, pausedTicks;
    bool started, paused;
    
    DISALLOW_COPY_AND_ASSIGN(Timer);
};

#endif
