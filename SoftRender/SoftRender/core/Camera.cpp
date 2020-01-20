#include "Camera.h"



void Camera::updateTransfrom(Vector3 position, Vector3 forwardDir, Vector3 upDir=Vector3(0,1,0)) {
    m_Position = position;
    m_ForwardDir = forwardDir;
    m_UpDir = upDir;
    updateViewMatrix();
}


void Camera::updateViewMatrix() {
    
}

void Camera::updateProjectionMatrix() {

}