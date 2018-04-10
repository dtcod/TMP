#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <string>
#include <vector>
#include <functional>
#include <array>
class meshObject
{
public:
    meshObject(std::string filename);
private:

    static GLuint vao;
    static GLuint vbo;
    std::vector<std::array<float, 3>> _v;
    std::vector<std::array<int, 3>> _f;
//    std::function<void(void)> generateGLBuffer = [=](void){
//        this->vao =
//    };
};

#endif // MESHOBJECT_H
