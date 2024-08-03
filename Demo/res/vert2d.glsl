#version 400 core

// layout(location=0) in vec3 i_vert;
layout(location=0) in vec3 i_pos;
layout(location=1) in vec3 i_color;
// layout(location=3) in vec2 i_scale;
// layout(location=4) in float i_angle;

uniform mat4 u_proj;

out vec3 v_color;

float pi = 3.141592;

vec3 rotateZ(vec3 vert, float angle){
	vec3 rotated = vec3(0.0f);
	rotated.x = vert.x * cos(angle) - vert.y * sin(angle);
	rotated.y = vert.x * sin(angle) + vert.y * cos(angle);
	rotated.z = vert.z;
	return rotated;
}

void main() {
	// vec3 pos = rotateZ(i_vert, i_angle * (pi/180.0f));
	// pos *= i_scale;
	// pos += i_pos;
	gl_Position = u_proj * vec4(i_pos, 1.0f);
	v_color = i_color;
}