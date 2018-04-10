#version 430
out vec4 color;
in vec3 light_norm;
void main()
{
    color.xyz = 0.2f*vec3(1.0f,1.0f,1.0f)+0.4f*vec3(0.3,0.3,0.6)*dot(vec3(0,0,-1),light_norm);
    color.w = 1.0f;
}
