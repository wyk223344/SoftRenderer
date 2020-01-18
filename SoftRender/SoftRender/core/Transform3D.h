#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "../math/Vector3.h"
#include "../math/Matrix4x4.h"
#include "../math/Quaternion.h"


class Transform3D {
public:
    Transform3D(): m_IsDirty(false) {};
    void setPosition(float x, float y, float z);
    void setEularRotation(float yaw, float pitch, float roll);
    void setQuaternionRotation(float x, float y, float z, float w);
private:
    Vector3 m_Position;
    Vector3 m_EulerRotation;
    Quaternion m_QuaternionRotation;
    Matrix4x4 m_LocalMatrix;
    Matrix4x4 m_WorldMatrix;
    bool m_IsDirty;
};

#endif