#version 330 core
layout (location = 0) in vec3 a_vert_pos;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
    gl_Position = u_p * u_v * u_m * vec4(a_vert_pos, 1.0);
}