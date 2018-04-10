#ifndef FBO_RENDERER_H
#define FBO_RENDERER_H

#include <QtQuick/QQuickFramebufferObject>



class FboNode:public QQuickFramebufferObject
{
    Q_OBJECT
public:
    FboNode();

    QQuickFramebufferObject::Renderer *createRenderer() const ;

public slots:
    void move(int x, int y);
    void rotate(int x, int y);
    void doubleClick(int x,int y);
private:

};

#define FNode FboNode

#endif // FBO_RENDERER_H
