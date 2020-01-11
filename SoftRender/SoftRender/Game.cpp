#include "Game.h"



Game Game::Create() {
    Game game = Game();
    game.init();
    return game;
};


void Game::start() {
    loop();
};



void Game::init() {
    m_Window = Window::Create("View", 800, 600);
};


void Game::loop() {

    while (!m_Window.shouldClose())
    {
        /* code */
        Sleep(100);
    }
    
};



void DrawLine(int x0, int y0, int x1, int y1) {

}

