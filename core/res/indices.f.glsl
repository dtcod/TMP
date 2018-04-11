#version 430
out vec4 color;
in vec3 light_norm;
uniform vec3 base_color = vec3(0.2f, 0.2f, 0.2f);
void main()
{
    color.xyz = base_color+0.4f*vec3(0.3,0.3,0.6)*dot(vec3(0,0,-1),light_norm);
    color.w = 1.0f;
}
