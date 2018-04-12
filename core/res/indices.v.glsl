#version 430
layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 norm;
uniform mat4 model;
out vec3 light_norm_vs;
void main()
{
    light_norm_vs = normalize(mat3(model)*norm);
    gl_Position = model*vec4(vert,1.0);
}
