#include "meshObject.h"
#include <TMRenderer.h>
#include <fstream>
GLuint meshObject::vao = 0;
GLuint meshObject::vbo = 0;

meshObject::meshObject(std::string filename)
{
    std::fstream fileHandle;
    fileHandle.open(filename,std::ifstream::in);
    if(!fileHandle.is_open()) return;
    char tmpLine[500];
    std::array<float, 3> Av;
    std::array<int, 3> Af;
    for(;fileHandle.getline(tmpLine,500);){
        if ( tmpLine[0] == '#' ) continue;
        char *start;
        if((start=strstr(tmpLine,"v "))){
            sscanf(start,"v %f%f%f",&Av[0],&Av[1],&Av[2]);
            _v.push_back(Av);
        }else if((start=strstr(tmpLine,"f "))){
            sscanf(start,"f %d%d%d",&Af[0],&Af[1],&Af[2]);
            Af[0]--; Af[1]--; Af[2]--;
            _f.push_back(Af);
        }
    }
    fileHandle.close();
}
