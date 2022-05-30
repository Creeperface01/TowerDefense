#pragma once

#include <centurion.hpp>

class Fps {
public:
    explicit Fps(int tickInterval = 30)
            : m_tickInterval(tickInterval), m_nextTime(SDL_GetTicks() + tickInterval) {
    }

    void next() {
        SDL_Delay(getTicksToNextFrame());

        m_nextTime += m_tickInterval;
    }

private:
    const int m_tickInterval;
    Uint32 m_nextTime;

    Uint32 getTicksToNextFrame() const {
        Uint32 now = SDL_GetTicks();

        return (m_nextTime <= now) ? 0 : m_nextTime - now;
    }
};
