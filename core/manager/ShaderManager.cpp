#include "ShaderManager.h"
#include <glm/gtc/type_ptr.hpp>
#include <manager/CameraManager.h>
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

void ShaderManager::draw(std::string shader, meshObject* mesh, std::function<void ()> ex_f) {
    SMP[shader]->bind();
    SMP[shader]->setUniformValue("camera_vp", QMatrix4x4(CM->vp_pointer(), 4, 4));
    SMP[shader]->setUniformValue("model", mesh->getModel());
    if(ex_f)    ex_f();
    SMP[shader]->release();
}
