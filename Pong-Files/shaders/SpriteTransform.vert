#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main(void) {
	TexCoords = vertex.zw;
	gl_Position = projection * model * vec4(vertex.x, vertex.y, 0.0, 1.0);
}