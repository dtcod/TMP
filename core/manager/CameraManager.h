#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include <glm/glm.hpp>

class CameraManager
{
public:
    static CameraManager* getCameraManager(){
        static CameraManager* self = nullptr;
        if(self == nullptr)
            self = new CameraManager();
        return self;
    }

    float* vp_pointer();

    void move(int x, int y);

    void updateSize(int width, int height);

private:
    CameraManager();
    glm::mat4 camera_vp;
    glm::vec3 Pos   = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up    = glm::vec3(0.0f, 1.0f, 0.0f);
    float ratio = 1.0f;
};

#define CM  CameraManager::getCameraManager()

#endif // CAMERAMANAGER_H
