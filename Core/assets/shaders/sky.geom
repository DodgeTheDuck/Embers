#version 420 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

void main() {

	double halfWidth = 1920.0/1.99;
	double halfHeight = 1080.0/1.99;

	gl_Position = vec4(-halfWidth, -halfHeight, 0.999999, 1);
	EmitVertex();
	gl_Position = vec4(halfWidth, -halfHeight, 0.9999999, 1);
	EmitVertex();
	gl_Position = vec4(-halfWidth, halfHeight, 0.9999999, 1);
	EmitVertex();
	gl_Position = vec4(halfWidth, halfHeight, 0.9999999, 1);
	EmitVertex();

}