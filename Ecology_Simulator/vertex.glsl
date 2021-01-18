#version 330 core

// Postion and texture coords
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 txture;

out vec2 textureCoords;

uniform mat4 model;
uniform mat4 projection;

void main(){
	// Transform raw vertex to projection
	gl_Position = projection * model * vec4(pos, 0.0f, 1.0f);
	textureCoords = txture;
}