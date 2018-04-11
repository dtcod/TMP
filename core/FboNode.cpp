#include "FboNode.h"
#include <easylogging++.h>
#include <TMRenderer.h>
#include <manager/CameraManager.h>
#include <manager/ShaderManager.h>
#include <utils/Select.h>
FboNode::FboNode()
{

}
QQuickFramebufferObject::Renderer* FboNode::createRenderer() const {
    return new TMRenderer();
}

void FboNode::move(int x, int y) {
    CM->move(x, y);
    TM->render_semaphore.release();
}

void FboNode::rotate(int x, int y) {
    TMESH->rotate(x, y);
    TM->render_semaphore.release();
}

void FboNode::scaleBy(float s) {
    TMESH->scaleBy(s);
    TM->render_semaphore.release();
}

void FboNode::doubleClick(int x, int y) {
    TM->update();
    TM << [=](void){
        auto picks = SPM->pickFace([=](void){
            TGL.glClearColor(-1.0f, 0.0f, 0.0f, 1.0f);
            TGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SM->draw("picker",TMESH,[=]{
                TMESH->indicesDraw();
            });
        }, std::vector<std::pair<int,int>>(1, std::make_pair(x,y)));
        LOG(INFO) << picks.size() ;
//        SM->draw("indices",TMESH,[=]{
//            SMP["indices"]->setUniformValue("base_color",QVector3D(0.6f,0.1f,0.1f));
//            TMESH->indicesDraw(picks[0],1);
//        });
        TM->callback_semaphore.release();
    };
    TM->render_semaphore.release();
    TM->callback_semaphore.acquire();
}

