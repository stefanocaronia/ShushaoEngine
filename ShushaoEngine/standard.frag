R"(#version 330 core

	in vec2 TexCoord;

	uniform sampler2D textureSamplerID;
	uniform vec3 renderColor;

	out vec3 Color;

	void main() {

		Color = texture(baseImage, TexCoord).rgb;
		// * vec4(renderColor, 1.0);

	}
)"
