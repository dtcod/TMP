#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <string>
#include <vector>
#include <functional>
#include <array>
#include <glm/glm.hpp>
#include <functional>
#include <QMatrix4x4>
struct  VertItem{
    VertItem(){
        mn =  glm::vec3(0);
        mv =  glm::vec3(0);
    }
    glm::vec3 mv;
    glm::vec3 mn;
};

class meshObject
{
public:
    meshObject(std::string filename);
    void rotate(int dx, int dy);
    void scaleBy(float s);
    QMatrix4x4 getModel();
    void indicesDraw(int start=0, int count=-1);
private:
    GLuint vao;
    GLuint vbo, ibo;
    glm::mat4 model;
    std::vector<VertItem> _v;
    std::vector<std::array<int, 3>> _f;
    void centerlized();
    bool readObj(std::string file);
    bool readOff(std::string file);
    void initGLVertexArrays();
    void syncGLVertexArrays();
    void write(std::string file);
    void calculateNorm();
};

#endif // MESHOBJECT_H
