#include "Game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "core/Model.h"
#include "core/Util.h"


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
    m_FrameBuffer = FrameBuffer::Create(800, 600, 4);

    Vector3 test = Vector3(1.0f, 2.0f, 3.0f);
    std::cout << test[0] << ";" << test[1] << ";" << test[2] << std::endl;
    test[0] = 1000;
    std::cout << test[0] << ";" << test[1] << ";" << test[2] << std::endl;
};



void Game::loop() {
    Model model = Model("../Assets/african_head/african_head.obj");
    std::cout << "Vertex Size:" << model.m_Vertexes.size() << std::endl;

    Vector4 whiteColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    Vector4 redColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    Vector4 greenColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    Vector4 blueColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);


    Vector3 lightDir = Vector3(0, 0, -1).normalize();
    for (int i = 0; i < model.m_Vertexes.size(); i+=3) {
        Vector2 screenCoords[3];
        Vector3 worldCoords[3];
        for (int j = 0; j < 3; j++) {
            Vertex v0 = model.m_Vertexes[i + j];
            Vertex v1 = model.m_Vertexes[i + (j + 1) % 3];
            int x0 = v0.position.x * 300 + 400;
            int y0 = (v0.position.y + 1.) * 300;
            int x1 = v1.position.x * 300 + 400;
            int y1 = (v1.position.y + 1.) * 300;
            screenCoords[j] = Vector2(x0, y0);
            worldCoords[j] = v0.position;
        }
        Vector3 n = (worldCoords[2]-worldCoords[0]).cross(worldCoords[1] - worldCoords[0]);
        n.normalize();
        float intensity = n.dot(lightDir);
        // std::cout << intensity << std::endl;
        if (intensity > 0) {
            // std::cout << intensity << std::endl;
            Vector4 color = Vector4(intensity, intensity, intensity, 1.0f);
            Util::DrawTriangle(screenCoords[0], screenCoords[1], screenCoords[2], m_FrameBuffer, color);
        }
    }

    // DrawLine(20, 13, 400, 200, m_FrameBuffer, Vector4(1, 1, 1, 1));
    // DrawLine(20, 13, 50, 500, m_FrameBuffer, Vector4(0, 1, 0, 1));


    m_Window.drawBuffer(m_FrameBuffer);
    Sleep(10000);

    // while (!m_Window.shouldClose())
    // {
    //     /* code */
    //     // DrawLine(20, 13, 400, 200, m_FrameBuffer, Vector4(1, 0, 0, 1));
    //     // DrawLine(20, 13, 50, 500, m_FrameBuffer, Vector4(0, 1, 0, 1));


    //     m_Window.drawBuffer(m_FrameBuffer);

    //     Sleep(1000);
    // }
    
};





