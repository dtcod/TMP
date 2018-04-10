#ifndef SELECTMANAGER_H
#define SELECTMANAGER_H
#include <QOpenGLBuffer>
#include <functional>
#include <vector>
class SelectManager
{
public:
    static SelectManager* getSelectManager(){
        static SelectManager* self = nullptr;
        if(self == nullptr)
            self = new SelectManager();
        return self;
    }
    void createAttchment(unsigned int x, unsigned int y);
    void pickFace(std::function<void(void)> pick_f, std::vector<std::pair<int,int>> xys);
private:
    SelectManager();
    GLuint m_fbo, m_rbo[2];
};
#define SPM  SelectManager::getSelectManager()
#endif // SELECTMANAGER_H
