#version 420 core

out vec4 o_frag_color;

layout(binding = 1) uniform sampler2D u_grass;
layout(binding = 2) uniform sampler2D u_stone;

uniform vec3 view_pos;

in GS_OUT {
    vec2 uv;
    vec3 frag_pos;
    vec3 normal;
} fs_in;

void main()
{
 
    vec3 ambient = vec3(0.3, 0.3, 0.3);
    float shininess = 0.5;
    vec3 light_col = vec3(1.0, 1.0, 1.0);
    vec3 light_dir = normalize(vec3(0.5, -1.0, 0.5));
    vec3 view_dir    = normalize(view_pos - fs_in.frag_pos);
    vec3 half_dir = normalize(light_dir + view_dir);

    vec4 tex_grass = texture(u_grass, fs_in.uv);
    vec4 tex_stone = texture(u_stone, fs_in.uv);

    vec3 normal = normalize(fs_in.normal);       
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff * light_col;

    vec3 lighting = mix(tex_grass, tex_stone, fs_in.frag_pos.y / 10.0).rgb;
    o_frag_color = vec4(lighting, 1.0);


}