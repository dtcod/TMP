#include "ShaderManager.h"
ShaderManager::ShaderManager()
{
    program["indices"] = new QOpenGLShaderProgram();
    program["picker"]  = new QOpenGLShaderProgram();
}

void ShaderManager::initialize(){
    SMP["indices"]->addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/indices.v.glsl");
    SMP["indices"]->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/indices.f.glsl");
    SMP["indices"]->link();

    SMP["picker"]->addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/indices.v.glsl");
    SMP["picker"]->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/indices.picker.f.glsl");
    SMP["picker"]->link();
}
