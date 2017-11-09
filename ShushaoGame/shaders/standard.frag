#version 330 core

in vec2 TexCoord;
uniform sampler2D textureSamplerID;
uniform vec4 renderColor;

out vec4 Color;

void main() {
	Color = texture(textureSamplerID, TexCoord).rgba * vec4(renderColor);
}
