#ifndef GAME_H
#define GAME_H

#include "window/Window.h"

class Game {
public:
    static Game Create();
    void start();
private:
    Window m_Window;

    void init();
    void loop();
};

#endif