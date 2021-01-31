#version 330 core
in vec2 textureCoords;

uniform sampler2D image;

out vec4 fragColor;

void main(){
	vec4 color = texture(image, textureCoords, 0.0f);
	if (color.a < 0.2) discard;
	// Make them red - do with uniform on death? depleting var for alpha? when depleted delete entity?
	//fragColor = mix(color, vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.5f);
	fragColor = color;
}