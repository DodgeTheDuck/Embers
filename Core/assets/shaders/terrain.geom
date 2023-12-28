#version 420 core

layout(points) in;
layout(triangle_strip, max_vertices = 64) out;

layout(binding = 0) uniform sampler2D u_height_map;

in VS_OUT {
    mat4 vp;
	unsigned int chunk_x;
    unsigned int chunk_y;
	unsigned int max_chunks;
	float scale;
	unsigned int lod;
} gs_in[];

out GS_OUT {
	vec2 uv;
	vec3 frag_pos;
	vec3 normal;
} gs_out;

void main() {

	double max_quads = 5;
	float scale = 10;

	double n_quads = ceil(max_quads / min(max_quads,  gs_in[0].lod));
	double offset_x = gs_in[0].chunk_x;
	double offset_y = gs_in[0].chunk_y;
	double quad_size = 1.0 / n_quads;
	
	double max_chunks = double(gs_in[0].max_chunks);
	double sample_offset_x = offset_x / max_chunks;
	double sample_offset_y = offset_y / max_chunks;
	double sample_size = quad_size / max_chunks;

	vec4 p;
	double x, y, z, u, v;

	for(int i = 0; i < n_quads+1; i++) {
		for(int j = 0; j < n_quads+1; j++) {

			x = double(i) * quad_size + offset_x;
			z = double(j) * quad_size + offset_y;
			u = sample_offset_x + i * sample_size;
			v = sample_offset_y + j * sample_size;
			
			y = texture(u_height_map, vec2(u, v)).r * scale;
			p = vec4(x, y, z, 1.0);
			gl_Position = gs_in[0].vp * p;
			gs_out.uv = vec2(0, 0);
			gs_out.frag_pos = p.xyz;
			EmitVertex();

			y = texture(u_height_map, vec2(u + sample_size, v)).r * scale;
			p = vec4(x + quad_size, y, z, 1.0);
			gl_Position = gs_in[0].vp * p;
			gs_out.uv = vec2(1, j % 2);
			gs_out.frag_pos = p.xyz;
			EmitVertex();
			
		}

		EndPrimitive();
		
	}

}