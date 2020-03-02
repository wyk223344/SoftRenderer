#include "Game.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "core/Model.h"
#include "core/Camera.h"
#include "util/Util.h"
#include "math/Matrix4x4.h"

#pragma comment(lib, "winmm.lib ")



void test() {
    std::cout << "test start----------------->" << std::endl;
    OperateRecord operateRecord;
    float temp;
    if (operateRecord.isLeftBtnDown) {temp = 1;}
    else {temp = 0;}
    std::cout << temp << std::endl;
    operateRecord.isLeftBtnDown = true;
    if (operateRecord.isLeftBtnDown) {temp = 1;}
    else {temp = 0;}
    std::cout << temp << std::endl;
    std::cout << "test end------------------->" << std::endl;
}


Game::Game() {
    Window::RegisterWindowClass();
    m_Window = new Window("View", WINDOW_WIDTH, WINDOW_HEIGHT);
    m_FrameBuffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
};

Game::~Game() {
    if(m_Window) delete m_Window;
    if(m_FrameBuffer) delete m_FrameBuffer;
    m_Window = nullptr;
    m_FrameBuffer = nullptr;
};


void Game::start() {
    loop();
};


void input_poll_events(void) {
    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}


void Game::loop() {
    Model model = Model("../Assets/african_head/african_head.obj");

    Vector4 whiteColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
    Vector4 redColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    Vector4 greenColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    Vector4 blueColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    int width = m_FrameBuffer->getWidth();
    int height = m_FrameBuffer->getHeight();
    float *zBuffer = new float[width * height];
   
    float distance = 2.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    Camera camera(45.0f, float(WINDOW_WIDTH) / WINDOW_HEIGHT);
    camera.updateTransfrom(Vector3(1, 0, 2), Vector3(0, 0, 0));
    Matrix4x4 matrixViewProjection;

    Vector3 lightDir = Vector3(0, 0, -1).normalize();

    int curTime, deltaTime, preTime = timeGetTime();

    boolean isInTouch = false;
    float touchX, touchY, preTouchX, preTouchY;

    float ratio = 0.01;
    float temp;

    Window &window = *m_Window;
    while (!false)
    {
        m_FrameBuffer->clean();

        curTime = timeGetTime();
        deltaTime = curTime - preTime;

        window.updateOperateRecord();

        OperateRecord &operateRecord = *window.getOperateRecord();

        if (isInTouch) {
            if (operateRecord.isLeftBtnDown) {
                pitch += (operateRecord.y - preTouchY) * ratio;
                yaw += -(operateRecord.x - preTouchX) * ratio;
                preTouchY = operateRecord.y;
                preTouchX = operateRecord.x;
            } else {
                isInTouch = false;
            }
        } else {
            if (operateRecord.isLeftBtnDown) {
                isInTouch = true;
                preTouchY = operateRecord.y;
                preTouchX = operateRecord.x;
            }
        }
        Vector3 cameraPos;
        cameraPos.y = std::sin(pitch) * distance;
        temp = std::cos(pitch) * distance;
        cameraPos.x = std::sin(yaw) * temp;
        cameraPos.z = std::cos(yaw) * temp;

        camera.updatePosition(cameraPos);

        matrixViewProjection = camera.m_ViewProjectionMatrix;

        for (int i=width*height; i--; zBuffer[i] = -(std::numeric_limits<float>::max)());
        
        for (int i = 0; i < model.m_Vertexes.size(); i+=3) {
            Vector3 screenCoords[3];
            Vector3 worldCoords[3];
            Vector2 uvs[3];
            for (int j = 0; j < 3; j++) {
                Vertex &v0 = model.m_Vertexes[i + j];
                Vector4 temp = matrixViewProjection * v0.position;
                screenCoords[j] = Vector3(int(temp.x / temp.w * 400.0f + 400.0f), int(temp.y / temp.w * 300.0f + 300.0f), -temp.z);
                worldCoords[j] = v0.position;
                uvs[j] = v0.texcoord;
            }
            Vector3 n = (worldCoords[2]-worldCoords[0]).cross(worldCoords[1] - worldCoords[0]);
            n.normalize();
            float intensity = n.dot(lightDir);
            if (intensity > 0) {
                DrawUtil::DrawTriangle(screenCoords, zBuffer, m_FrameBuffer, uvs, model.m_DiffuseMapImage, intensity);
            }
        }

        window.drawBuffer(m_FrameBuffer);

        preTime = curTime;
        input_poll_events();
    }
    
};





