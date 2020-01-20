#ifndef CAMERA_H
#define CAMERA_H

#include "Transform3D.h"

class Camera {
public:
    Transform3D m_Transform;

    Vector3 m_Position;
    Vector3 m_ForwardDir;
    Vector3 m_UpDir;

    Matrix4x4 m_ViewMatrix;
    Matrix4x4 m_ProjectionMatrix;

    float m_Fovy;
    float m_Aspect;

    Camera(float fovy, float aspect): m_Fovy(fovy), m_Aspect(aspect) { updateProjectionMatrix(); };
    void updateTransfrom(Vector3 position, Vector3 forwardDir, Vector3 upDir=Vector3(0,1,0));
private:
    void updateViewMatrix();
    void updateProjectionMatrix();
};


#endif