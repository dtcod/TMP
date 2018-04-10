#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <string>
#include <vector>
#include <functional>
#include <array>
#include <glm/glm.hpp>
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
    glm::mat4 model;
    void rotate(int dx, int dy);
    void draw(std::string shader);
private:
    GLuint vao;
    GLuint vbo, ibo;
    std::vector<VertItem> _v;
    std::vector<std::array<int, 3>> _f;
    void centerlized();
    void read(std::string file);
    void write(std::string file);
    void calculateNorm();
    void indicesDraw();
};

#endif // MESHOBJECT_H
