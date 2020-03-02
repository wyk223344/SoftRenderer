#ifndef CAMERA_H
#define CAMERA_H

#include "Transform3D.h"

class Camera {
public:
    Transform3D m_Transform;

    Vector3 m_Position;
    Vector3 m_Target;
    Vector3 m_UpDir;

    Matrix4x4 m_ViewMatrix;
    Matrix4x4 m_ProjectionMatrix;
    Matrix4x4 m_ViewProjectionMatrix;

    float m_Fovy;
    float m_Aspect;

    Camera(float fovy, float aspect): m_Fovy(fovy), m_Aspect(aspect) { updateProjectionMatrix(); };
    void updateTransfrom(Vector3 position, Vector3 target, Vector3 upDir=Vector3(0,1,0));

    void updatePosition(Vector3 position);

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateViewProjectionMatrix();
};


#endif