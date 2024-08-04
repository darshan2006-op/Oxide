#version 400 core

layout(location=0)in vec3 i_pos;
layout(location=1)in vec2 i_texCoords;

out vec2 v_texCoords;

void main() {
	vec3 pos = i_pos;
	pos.y *= 1.777;
	gl_Position = vec4(pos, 1.0f);
	v_texCoords = i_texCoords;
}