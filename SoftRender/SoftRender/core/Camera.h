#ifndef CAMERA_H
#define CAMERA_H

#include "Transform3D.h"

class Camera {
public:
    Transform3D m_Transform;

    void lookAt(Vector3 targetPosition, Vector3 upDirection);
private:
};


#endif