#include "Camera.h"
#include "../math/Matrix4x4.h"


void Camera::updateTransfrom(Vector3 position, Vector3 target, Vector3 upDir) {
    m_Position = position;
    m_Target = target;
    m_UpDir = upDir;
    updateViewMatrix();
}


void Camera::updatePosition(Vector3 position) {
    m_Position = position;
    updateViewMatrix();
}


void Camera::updateViewMatrix() {
    m_ViewMatrix = Matrix4x4::CreateViewMatrixByLookAt(m_Position, m_Target, m_UpDir, m_ViewMatrix);
    updateViewProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
    m_ProjectionMatrix = Matrix4x4::CreatePerspectiveProjectionMatrix(m_Fovy, m_Aspect, 0.1f, 10000.0f, m_ProjectionMatrix);
    updateViewProjectionMatrix();
}

void Camera::updateViewProjectionMatrix() {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}