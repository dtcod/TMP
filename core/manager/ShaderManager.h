#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <map>
#include <string>
#include <meshObject.h>
class ShaderManager
{
public:
    static ShaderManager* getShaderManager(){
        static ShaderManager* self = nullptr;
        if(self == nullptr)
            self = new ShaderManager();
        return self;
    }
    std::map<std::string,QOpenGLShaderProgram*> program;
    void initialize();
    void draw(std::string shader, meshObject* mesh, std::function<void(void)> ex_f=nullptr);
private:

    ShaderManager();
};

#define SM ShaderManager::getShaderManager()
#define SMP ShaderManager::getShaderManager()->program
#endif // SHADERMANAGER_H
