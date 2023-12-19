#version 330 core
layout (location = 0) in vec3 a_vert_pos;
layout (location = 3) in mat4 a_vert_instance_transform;

uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
    gl_Position = u_p * u_v * a_vert_instance_transform * vec4(a_vert_pos, 1.0);
}