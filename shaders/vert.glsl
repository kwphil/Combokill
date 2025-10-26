#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

uniform mat4 MVP;

out vec3 vCol;

void main() {
	gl_Position = MVP * vec4(aPos, 1.0);
	vCol = aCol;
}
