#ifndef TMRENDERER_H
#define TMRENDERER_H

#include <QOpenGLFunctions_4_5_Core>
#include <QtQuick/QQuickFramebufferObject>
#include <functional>
#include <QReadWriteLock>
#include <QSemaphore>
#include <list>
#include <map>
#include <meshObject.h>
class TMRenderer: public QQuickFramebufferObject::Renderer{
    void render() override ;
    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
public:
    void update();
    void rotate(int dx, int dy);
    TMRenderer();
    static QOpenGLFunctions_4_5_Core& getGL(){
        return self->gl;
    }
    static TMRenderer* self;
    meshObject* tmesh = nullptr;
    QSemaphore callback_semaphore;
    QSemaphore render_semaphore;
private:
    ~TMRenderer();
    QOpenGLFunctions_4_5_Core gl;
    std::list<std::function<void(void)>> anonymous_caller;
    std::map<std::string,std::function<void(void)> > named_caller;
    friend TMRenderer *operator << (TMRenderer *t,std::function<void(void)> op ) {
        t->call_lock.lockForWrite();
        t->anonymous_caller.push_back(op);
        t->call_lock.unlock();
        return t;
    }
    friend TMRenderer *operator << (TMRenderer *t,std::pair< std::string,std::function<void(void)>> op) {
        t->call_lock.lockForWrite();
        t->named_caller[op.first] = op.second;
        t->call_lock.unlock();
        return t;
    }
    QReadWriteLock call_lock;
};
#define TGL TMRenderer::getGL()
#define TM TMRenderer::self
#define TMESH TMRenderer::self->tmesh
#endif // TMRENDERER_H
