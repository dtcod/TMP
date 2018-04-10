#include "Select.h"
#include <TMRenderer.h>
#include <easylogging++.h>
SelectManager::SelectManager()
{
    TGL.glCreateFramebuffers(1, &m_fbo);
    TGL.glCreateRenderbuffers(2, m_rbo);
}


void SelectManager::createAttchment(unsigned int x, unsigned int y) {
    TGL.glNamedRenderbufferStorage(m_rbo[0], GL_RGB32F, x, y);
    TGL.glNamedFramebufferRenderbuffer(m_fbo, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_rbo[0]);

    TGL.glNamedRenderbufferStorage(m_rbo[1], GL_DEPTH_COMPONENT24, x, y);
    TGL.glNamedFramebufferRenderbuffer(m_fbo, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo[1]);
    GLenum Status = TGL.glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
    }
    TGL.glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SelectManager::pickFace(std::function<void ()> pick_f, std::vector<std::pair<int,int>> xys){
    TGL.glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
    pick_f();
    TGL.glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fbo);
    TGL.glReadBuffer(GL_COLOR_ATTACHMENT0);
    std::vector<int> pick_res;
    float rgb[3];
    for(auto& e: xys){
        LOG(INFO) << e.first << ' ' << e.second;
        TGL.glReadPixels(e.first, e.second, 1, 1, GL_RGB, GL_FLOAT, rgb);
        LOG(INFO) << rgb[0] << ' ' << rgb[1] << ' ' << rgb[2];
    }
    TGL.glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    TGL.glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
