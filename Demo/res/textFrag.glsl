#version 400 core

out vec4 o_color;

in vec2 v_texCoords;

uniform sampler2D u_texUnit;

void main(){
	o_color = texture(u_texUnit, v_texCoords);
}
