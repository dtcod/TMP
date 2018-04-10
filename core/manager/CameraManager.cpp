#include "CameraManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FboNode.h>
#include <easylogging++.h>
CameraManager::CameraManager()
{

}

float* CameraManager::vp_pointer(){
    return glm::value_ptr(camera_vp);
}

void CameraManager::updateSize(int width, int height){
    ratio = width/(float)height;
    camera_vp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.1f, 100.0f) * glm::lookAt(Pos, Pos + Front, Up);
//    camera_vp = glm::perspective(45.0f, ratio, 0.01f, 1000.0f)* glm::lookAt(Pos, Pos + Front, Up);
}

void CameraManager::move(int x, int y){
    if (abs(x) < abs(y)) {
        Pos -= Up * (0.002f * y);
    } else {
        Pos += glm::cross(Up, Front) * (0.002f * x);
    }
    camera_vp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.000001f, 100.0f) * glm::lookAt(Pos, Pos + Front, Up);
}
