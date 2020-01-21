#include "Game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "core/Model.h"
#include "core/Util.h"
#include "core/Camera.h"

#include "math/Matrix4x4.h"

void test() {
    std::cout << "test start----------------->" << std::endl;
    Matrix4x4 mat;
    std::cout << mat.elements[0][3] << std::endl;
    mat[0][3] = 1;
    std::cout << mat.elements[0][3] << std::endl;
    std::cout << "test end------------------->" << std::endl;
}


Game Game::Create() {
    Game game = Game();
    game.init();
    return game;
};


void Game::start() {
    loop();
};



void Game::init() {
    test();
    m_Window = Window::Create("View", WINDOW_WIDTH, WINDOW_HEIGHT);
    m_FrameBuffer = FrameBuffer::Create(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
};



void Game::loop() {
    Model model = Model("../Assets/african_head/african_head.obj");
    std::cout << "Vertex Size:" << model.m_Vertexes.size() << std::endl;

    Vector4 whiteColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    Vector4 redColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    Vector4 greenColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    Vector4 blueColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    int width = m_FrameBuffer.getWidth();
    int height = m_FrameBuffer.getHeight();
    float *zBuffer = new float[width * height];
    for (int i=width*height; i--; zBuffer[i] = -(std::numeric_limits<float>::max)());

    Camera camera(45.0f, float(WINDOW_WIDTH) / WINDOW_HEIGHT);
    camera.updateTransfrom(Vector3(0, 0, 30.0f), Vector3(0, 0, 0));
    Matrix4x4 matrixViewProjection = camera.m_ViewProjectionMatrix;
    matrixViewProjection.print();
    camera.m_ViewMatrix.print();
    camera.m_ProjectionMatrix.print();
    camera.updateTransfrom(Vector3(0, 0, 3.0f), Vector3(0, 0, 0));
    camera.m_ViewProjectionMatrix.print();
    camera.m_ViewMatrix.print();
    camera.m_ProjectionMatrix.print();

    Vector3 lightDir = Vector3(0, 0, -1).normalize();
    for (int i = 0; i < model.m_Vertexes.size(); i+=3) {
        Vector3 screenCoords[3];
        Vector3 worldCoords[3];
        Vector2 uvs[3];
        for (int j = 0; j < 3; j++) {
            Vertex v0 = model.m_Vertexes[i + j];
            // int x0 = v0.position.x * 300 + 400;
            // int y0 = (v0.position.y + 1.) * 300;
            Vector3 temp = matrixViewProjection * v0.position;
            screenCoords[j] = Vector3(temp.x * 400.0f + 400.0f, temp.y * 300.0f + 300.0f, temp.z);
            worldCoords[j] = v0.position;
            uvs[j] = v0.texcoord;
        }
        Vector3 n = (worldCoords[2]-worldCoords[0]).cross(worldCoords[1] - worldCoords[0]);
        n.normalize();
        float intensity = n.dot(lightDir);
        // std::cout << intensity << std::endl;
        if (intensity > 0) {
            // std::cout << intensity << std::endl;
            // Vector4 color = Vector4(intensity, intensity, intensity, 1.0f);
            Util::DrawTriangle(screenCoords, zBuffer, m_FrameBuffer, uvs, model.m_DiffuseMapImage, intensity);
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





