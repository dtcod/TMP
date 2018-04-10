#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <map>
#include <string>
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
private:

    ShaderManager();
};

#define SM ShaderManager::getShaderManager()
#define SMP ShaderManager::getShaderManager()->program
#endif // SHADERMANAGER_H
