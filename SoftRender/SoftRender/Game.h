#ifndef GAME_H
#define GAME_H

#include "window/Window.h"
#include "core/FrameBuffer.h"

class Game {
public:
    static Game Create();
    void start();
private:
    Window m_Window;
    FrameBuffer m_FrameBuffer;
    void init();
    void loop();
};

#endif