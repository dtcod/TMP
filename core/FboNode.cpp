#include "FboNode.h"
#include <easylogging++.h>
#include <TMRenderer.h>
#include <manager/CameraManager.h>
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
    TM->rotate(x, y);
    TM->render_semaphore.release();
}

void FboNode::doubleClick(int x, int y) {
    TM->update();
    TM << [=](void){
        SPM->pickFace([=](void){
            TGL.glClearColor(-1.0f, 0.0f, 0.0f, 1.0f);
            TGL.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            TMESH->draw("picker");
        }, std::vector<std::pair<int,int>>(1, std::make_pair(x,y)));
        TM->callback_semaphore.release();
    };
    TM->render_semaphore.release();
    TM->callback_semaphore.acquire();
}

