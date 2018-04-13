#include "TMRenderer.h"
#include <easylogging++.h>
#include <QOpenGLFramebufferObjectFormat>
#include <manager/ShaderManager.h>
#include <manager/CameraManager.h>
#include <meshObject.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/Select.h>
TMRenderer* TMRenderer::self = nullptr;
TMRenderer::TMRenderer(){
    self = this;
    gl.initializeOpenGLFunctions();
    LOG(INFO) << "GL Version: "<< gl.glGetString(GL_VERSION);
    gl.glEnable(GL_DEPTH_TEST);
    SM->initialize();
#ifdef Q_OS_LINUX
    tmesh = new meshObject("/home/user/gitrepos/TMP/data/body.off"); //demo
#endif

#ifdef Q_OS_WIN
    tmesh = new meshObject("D:/gitrepos/TMP/data/bunny.obj"); //bunny FullBodyScan
#endif
    this << std::pair< std::string,std::function<void(void)>>("indices", [=](void){
        TGL.glClearColor(0.2, 0.3, 0.3, 1.0);
        TGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SM->draw("indices",TMESH,[=]{
            SMP["indices"]->setUniformValue("base_color",QVector3D(0.2f,0.2f,0.2f));
            TMESH->indicesDraw();
        });
    });
    this->render_semaphore.release(1);
}

QOpenGLFramebufferObject* TMRenderer::createFramebufferObject(const QSize &size){
    CM->updateSize(size.width(), size.height());
    SPM->createAttchment(size.width(), size.height());
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return  new QOpenGLFramebufferObject(size, format);
}

TMRenderer::~TMRenderer() {

}

void TMRenderer::render() {
    if(this->render_semaphore.tryAcquire()){
        call_lock.lockForRead();
        for(auto& e:this->anonymous_caller)
            e();
        anonymous_caller.clear();
        for(auto& e:this->named_caller)
            e.second();
        call_lock.unlock();
    }
    this->update();

}

void TMRenderer::update(){
    QQuickFramebufferObject::Renderer::update();
}
