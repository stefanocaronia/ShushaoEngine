#include "shaders/phongshader.h"
#include "scenemanager.h"
#include "../resources.h"

namespace se {

	using namespace std;
	using namespace glm;

	PhongShader::PhongShader() {
		name = "Phong Shader";

		VertexShaderCode = Resources::GetEmbeddedText(PHONGSHADER_VERT);
		FragmentShaderCode = Resources::GetEmbeddedText(PHONGSHADER_FRAG);
	}

	void PhongShader::Awake() {
		// material controlled uniforms
		AddUniform("Ambient reflection", "ambient_color", UniformType::COLOR);
		AddUniform("Diffuse reflection", "diffuse_color", UniformType::COLOR);
		AddUniform("Specular reflection", "specular_color", UniformType::COLOR);
		AddUniform("Shininess", "shininess", UniformType::FLOAT);

		AddUniform("Diffuse Map", "diffuse_map", UniformType::TEXTURE);
		AddUniform("Specular Map", "specular_map", UniformType::TEXTURE);
		AddUniform("Normal Map", "normal_map", UniformType::TEXTURE);

		// shader controlled uniforms (locked)
		AddShaderUniform("view_position", UniformType::VECTOR);
		AddShaderUniform("M", UniformType::MATRIX);
		AddShaderUniform("point_lights_number", UniformType::INTEGER);
		AddShaderUniform("spot_lights_number", UniformType::INTEGER);
		// AddShaderUniform("directional_light", UniformType::LIGHT);
		AddShaderUniform("enabled_diffuse_map", UniformType::INTEGER);
		AddShaderUniform("enabled_normal_map", UniformType::INTEGER);
		AddShaderUniform("enabled_specular_map", UniformType::INTEGER);
	}

	void PhongShader::Update() {

		int pointLightCount = 0;
		int spotLightCount = 0;

		for (Light* light : SceneManager::activeScene->ActiveLights) {
			UniformLight ul = light->GetUniform();
			switch (light->type) {
				case LightType::DIRECTIONAL:
					SetLight("directional_light", ul);
					break;

				case LightType::POINT:
					SetLight("point_lights[" + ts(pointLightCount++) + "]", ul);
					break;

				case LightType::SPOT:
					SetLight("spot_lights[" + ts(spotLightCount++) + "]", ul);
					break;

				case LightType::DISC:
				case LightType::RECTANGLE:
					break;
			}
		}

		SetInteger("point_lights_number", pointLightCount);
		SetInteger("spot_lights_number", spotLightCount);

		vec3 viewPosition = SceneManager::activeScene->activeCamera->transform->localPosition;
		SetVector("view_position", {viewPosition.x, viewPosition.y, viewPosition.z});
	}
}
