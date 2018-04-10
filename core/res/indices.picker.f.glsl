#version 430
out vec4 color;
void main()
{
    color = vec4(gl_PrimitiveID, gl_PrimitiveID, gl_PrimitiveID, 1); // gl_PrimitiveID
}
