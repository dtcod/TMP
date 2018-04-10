#version 430
layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 norm;
uniform mat4 camera_vp;
uniform mat4 model;
out vec3 light_norm;
void main()
{
    light_norm = normalize(mat3(model)*norm); //
    gl_Position = camera_vp*model*vec4(vert,1.0);//vec4(0.01*gl_VertexID, 0.01*gl_VertexID, 0.0, 0.0); //
}
