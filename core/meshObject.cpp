#include "meshObject.h"
#include <TMRenderer.h>
#include <fstream>
#include <easylogging++.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Select.h>
#include <manager/ShaderManager.h>
#include <manager/CameraManager.h>
meshObject::meshObject(std::string filename)
{
    read(filename);
    centerlized();
    calculateNorm();
    //        write(filename+".obj");
    LOG(INFO) <<"f: " <<_f.size() << " v: " << _v.size();
    TGL.glGenVertexArrays(1, &vao);
    TGL.glGenBuffers(1, &vbo);
    TGL.glGenBuffers(1, &ibo);
    TGL.glBindVertexArray(vao);
    TGL.glBindBuffer(GL_ARRAY_BUFFER, vbo);
    TGL.glBufferData(GL_ARRAY_BUFFER, _v.size()*sizeof(_v[0]), _v.data(), GL_STATIC_DRAW);
    TGL.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(_v[0]), (GLvoid*)0);
    TGL.glEnableVertexAttribArray(0);
    TGL.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(_v[0]), (GLvoid*)sizeof(_v[0].mn));
    TGL.glEnableVertexAttribArray(1);
    TGL.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    TGL.glBufferData(GL_ELEMENT_ARRAY_BUFFER, _f.size()*sizeof(_f[0]), _f.data(), GL_STATIC_DRAW);

    TGL.glBindVertexArray(0);
}

void meshObject::read(std::string filename){
    std::fstream fileHandle;
    fileHandle.open(filename,std::ifstream::in);
    if(!fileHandle.is_open()) {
        LOG(INFO) << "failed to load obj: " << filename;
        return;
    }
    char tmpLine[500];
    VertItem Av;
    std::array<int, 3> Af;
    for(;fileHandle.getline(tmpLine,500);){
        if ( tmpLine[0] == '#' ) continue;
        char *start;
        if((start=strstr(tmpLine,"v "))){
            sscanf(start,"v %f%f%f",&Av.mv[0],&Av.mv[1],&Av.mv[2]);
            _v.push_back(Av);
        }else if((start=strstr(tmpLine,"f "))){
            sscanf(start,"f %d%d%d",&Af[0],&Af[1],&Af[2]);
            Af[0]--; Af[1]--; Af[2]--;
            _f.push_back(Af);
        }
    }
    fileHandle.close();
}

void meshObject::write(std::string filename){
    std::fstream fileHandle;
    fileHandle.open(filename,std::ifstream::out);
    if(!fileHandle.is_open()) {
        LOG(INFO) << "failed to load obj: " << filename;
        return;
    }
    fileHandle<< "# v: " << _v.size() << "   f: " << _f.size() << '\n';
    for(int i=0;i< _v.size(); i++)
        fileHandle <<"v " <<_v[i].mv[0] << ' ' << _v[i].mv[1] << ' ' << _v[i].mv[2] << '\n';
    for(int i=0;i< _v.size(); i++)
        fileHandle <<"vn " <<_v[i].mn[0] << ' ' << _v[i].mn[1] << ' ' << _v[i].mn[2] << '\n';
    for(int i=0;i< _f.size(); i++)
        fileHandle <<"f " <<_f[i][0]+1 << ' ' << _f[i][1]+1 << ' ' << _f[i][2]+1 << '\n';
    fileHandle.close();
}


void meshObject::centerlized(){
    glm::vec3 center = std::accumulate(_v.begin(), _v.end(), glm::vec3(0),[=](glm::vec3 acc,VertItem& e){
        return acc+e.mv;
    })/(float)_v.size();
    float scale_k = std::sqrt(std::accumulate(_v.begin(), _v.end(), 0.0, [=](float s, VertItem& e){
        return std::max(s,glm::length(e.mv-center)* glm::length(e.mv-center));
    })); // /(float)_v.size())

    model = glm::scale(glm::mat4(), glm::vec3(1.4 / scale_k))*glm::translate(glm::mat4(), -center);
}

void meshObject::calculateNorm(){
    std::vector<float> acc(_v.size(),0);
    std::vector<glm::vec3> norms(_v.size(), glm::vec3(0));
    for(int i=0; i< _f.size(); i++) {
        glm::vec3 norm = glm::cross(_v[_f[i][0]].mv-_v[_f[i][1]].mv, _v[_f[i][2]].mv-_v[_f[i][1]].mv);
        for(int j=0; j< 3; j++){
            _v[_f[i][j]].mn += norm ;
            acc[_f[i][j]] ++;
        }
    }
    for(int i=0; i< _v.size(); i++){
        _v[i].mn = glm::normalize( _v[i].mn/acc[i] );
    }
}

void meshObject::rotate(int dx, int dy) {
    if (abs(dx) > abs(dy) && abs(dx) > 2) {
        model = glm::rotate(glm::mat4(), dx * 0.003f, glm::vec3(0, 1, 0)) * model;
    } else if (abs(dy) > abs(dx) && abs(dy) > 2) {
        model = glm::rotate(glm::mat4(),-dy * 0.003f, glm::vec3(1, 0, 0)) * model;
    }
}

void meshObject::indicesDraw() {
    TGL.glBindVertexArray(this->vao);
//    TGL.glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
//    TGL.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    TGL.glDrawElements(GL_TRIANGLES, this->_f.size()*3, GL_UNSIGNED_INT,0);
    TGL.glBindVertexArray(0);
}

void meshObject::draw(std::string shader) {
    SMP[shader]->bind();
    SMP[shader]->setUniformValue("camera_vp", QMatrix4x4(CM->vp_pointer(), 4, 4));
    SMP[shader]->setUniformValue("model", QMatrix4x4(glm::value_ptr(this->model), 4, 4));
    this->indicesDraw();
    SMP[shader]->release();
}
