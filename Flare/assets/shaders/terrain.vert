#version 420 core
layout (location = 0) in vec3 a_vert_pos;

uniform mat4 u_v;
uniform mat4 u_p;
uniform unsigned int u_max_chunks;
uniform float u_scale;
uniform vec3 u_cam_pos;

out VS_OUT {
    mat4 vp;
    unsigned int chunk_x;
    unsigned int chunk_y;
    unsigned int max_chunks;
    float scale;
    unsigned int lod;
} vs_out;

void main()
{    

    unsigned int chunk_x = gl_InstanceID % u_max_chunks;
    unsigned int chunk_y = uint(floor(gl_InstanceID / u_max_chunks));

    vs_out.vp = u_p * u_v;   
    vs_out.scale = u_scale;
    vs_out.max_chunks = u_max_chunks;
    vs_out.chunk_x = chunk_x;
    vs_out.chunk_y = chunk_y;
    vs_out.lod = 1;

//    float dx = u_cam_pos.x - chunk_x;
//    float dz = u_cam_pos.z - chunk_y;
//
//    //double dist = abs(sqrt(pow(dx,2) + pow(dz, 2))) / 2.0;
//    vs_out.lod = 1 + int(floor(dist));
//
}