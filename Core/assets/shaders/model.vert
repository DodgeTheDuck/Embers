#version 420 core
layout (location = 0) in vec3 a_vert_pos;
layout (location = 1) in vec3 a_vert_col;
layout (location = 2) in vec2 a_vert_uv;
layout (location = 3) in vec3 a_vert_normal;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;
uniform mat3 u_normal_matrix;

out vec3 frag_pos_world;
out vec2 frag_uv;
out vec3 frag_normal;

void main()
{
    gl_Position = u_p * u_v * u_m * vec4(a_vert_pos, 1.0);
    frag_uv = a_vert_uv;
    frag_normal = u_normal_matrix * a_vert_normal;
    frag_pos_world  = vec4(u_m * vec4(a_vert_pos, 1.0)).xyz;    
}