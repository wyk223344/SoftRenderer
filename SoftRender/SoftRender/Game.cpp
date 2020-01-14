#include "Game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "core/Model.h"

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
};


void DrawLine(int x0, int y0, int x1, int y1, FrameBuffer frameBuffer, Vector4 color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        // float t = (x - x0) / (float)(x1 - x0);
        // int y = y0 * (1.0 - t) + y1 * t;
        if (steep) {
            frameBuffer.drawPixel(y, x, color);
        } else {
            frameBuffer.drawPixel(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
};


void DrawTriangle(Vector2 t0, Vector2 t1, Vector2 t2, FrameBuffer frameBuffer, Vector4 color) {
    if (t0.y > t1.y) {
        std::swap(t0, t1);
    }
    if (t0.y > t2.y) {
        std::swap(t0, t2);
    }
    if (t1.y > t2.y) {
        std::swap(t1, t2);
    }
    int totalHeight = t2.y - t0.y;
    
};


void Game::loop() {
    Model model = Model("../Assets/african_head/african_head.obj");
    std::cout << "Vertex Size:" << model.m_Vertexes.size() << std::endl;

    Vector4 whiteColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < model.m_Vertexes.size(); i+=3) {
        for (int j = 0; j < 3; j++) {
            Vertex v0 = model.m_Vertexes[i + j];
            Vertex v1 = model.m_Vertexes[i + (j + 1) % 3];
            int x0 = (v0.position.x + 1.) * 400;
            int y0 = (v0.position.y + 1.) * 300;
            int x1 = (v1.position.x + 1.) * 400;
            int y1 = (v1.position.y + 1.) * 300;
            // std::cout << "(x:" << x0 << ",y:" << y0 << ")  (x:" << x1 << ",y:" << y1 << ")" << std::endl;
            DrawLine(x0, y0, x1, y1, m_FrameBuffer, whiteColor);
        }
    }

    // DrawLine(20, 13, 400, 200, m_FrameBuffer, Vector4(1, 1, 1, 1));
    // DrawLine(20, 13, 50, 500, m_FrameBuffer, Vector4(0, 1, 0, 1));

    // for (int i=0; i<model->nfaces(); i++) { 
    //     std::vector<int> face = model->face(i); 
    //     for (int j=0; j<3; j++) { 
    //         Vec3f v0 = model->vert(face[j]); 
    //         Vec3f v1 = model->vert(face[(j+1)%3]); 
    //         int x0 = (v0.x+1.)*width/2.; 
    //         int y0 = (v0.y+1.)*height/2.; 
    //         int x1 = (v1.x+1.)*width/2.; 
    //         int y1 = (v1.y+1.)*height/2.; 
    //         line(x0, y0, x1, y1, image, white); 
    //     } 
    // }

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





