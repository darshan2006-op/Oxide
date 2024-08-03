#version 400 core

layout(location=0) in vec3 i_pos;
layout(location=1) in vec3 i_color;

out vec3 v_color;

void main() {
	gl_Position = vec4(i_pos, 1.0f);
	v_color = i_color;
}