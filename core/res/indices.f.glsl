#version 430
out vec4 color;
in GS_FS{
    vec3 light_norm;
    noperspective  vec3 e_dis;
} fs_in;
uniform vec3 base_color = vec3(0.2f, 0.2f, 0.2f);
const vec4 wire_color = vec4(24/255.0, 25/255.0, 76/255.0, 1);
void wireframe(inout vec4 color) {
    color =  mix(wire_color, color, smoothstep(-0.001, 0.003,min(min(fs_in.e_dis.x,fs_in.e_dis.y),fs_in.e_dis.z)));
}

void main()
{
    color.xyz = base_color+0.4f*vec3(0.3,0.3,0.6)*dot(vec3(0,0,-1),fs_in.light_norm);
    color.w = 1.0f;
    wireframe(color);
}
