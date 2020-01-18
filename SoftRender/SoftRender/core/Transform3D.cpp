#include "Transform3D.h"


void Transform3D::setPosition(float x, float y, float z) {
    m_IsDirty = true;
    m_Position.x = x;
    m_Position.y = y;
    m_Position.z = z;
}


void Transform3D::setEularRotation(float yaw, float pitch, float roll) {
    m_IsDirty = true;
}


void Transform3D::setQuaternionRotation(float x, float y, float z, float w) {
    m_IsDirty = true;
}