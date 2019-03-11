#include "phongshader.h"
#include "scenemanager.h"

namespace se {

	using namespace std;
	using namespace glm;

	PhongShader::PhongShader() {
		name = "Mesh Shader";

		VertexShaderCode = R"glsl(#version 430

			layout(location=1) in vec3 vertex_coord;
			layout(location=2) in vec2 texture_coord;
			layout(location=4) in vec3 normal_value;

			layout(location=5) uniform mat4 MVP;
			uniform mat4 M;

			out vec2 UV;
			out vec3 Normal;
			out vec3 FragPos;

			void main() {
				gl_Position = MVP * vec4(vertex_coord, 1.0);
				FragPos = vec3(M * vec4(vertex_coord, 1.0));
				UV = texture_coord;
				// Normal = mat3(transpose(inverse(M))) * normal_value;
				Normal = normal_value;
			}

		)glsl";

		FragmentShaderCode = R"glsl(#version 430

			// TODO: Spotlight function

			#define MAX_POINT_LIGHTS 6
			#define MAX_SPOT_LIGHTS 6

			struct Light {
				vec3 position;
				vec3 direction;
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				float constant;
				float linear;
				float quadratic;
			};

			in vec3 Normal;
			in vec2 UV;
			in vec3 FragPos;

			uniform sampler2D diffuse_map;
			uniform sampler2D specular_map;
			uniform sampler2D normal_map;

			uniform bool enabled_diffuse_map;
			uniform bool enabled_normal_map;
			uniform bool enabled_specular_map;

			uniform vec4 ambient_color;
			uniform vec4 diffuse_color;
			uniform vec4 specular_color;
			uniform float shininess;

			uniform vec3 view_position;
			uniform Light directional_light;
			uniform Light point_lights[MAX_POINT_LIGHTS];
			uniform Light spot_lights[MAX_POINT_LIGHTS];
			uniform int point_lights_number;
			uniform int spot_lights_number;

			vec4 diffuse_map_fragcolor;
			vec4 specular_map_fragcolor;

			out vec4 frag_color;

			vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
			vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

			void main() {

				// properties
				vec3 norm;
				if (enabled_normal_map) {
					norm = normalize(texture(normal_map, UV).rgb * 2.0 - 1.0);
				} else {
					norm = normalize(Normal);
				}

				vec3 viewDir = normalize(view_position - FragPos);

				// Directional lighting
				vec3 result = CalcDirLight(directional_light, norm, viewDir);

				// Point lights
				for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
					if (i >= point_lights_number) break;
					result += CalcPointLight(point_lights[i], norm, FragPos, viewDir);
				}

				// phase 3: Spot light
				/* for(int i = 0; i < MAX_SPOT_LIGHTS; i++) {
					if (i >= spot_lights_number) break;
					result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
				} */

				frag_color = vec4(result, 1.0);
			}

			vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir) {

				vec3 lightDir = normalize(-light.direction);

				// diffuse shading
				float diff = max(dot(normal, lightDir), 0.0);

				// specular shading
				vec3 reflectDir = reflect(-lightDir, normal);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

				vec3 ambient, diffuse, specular;

				// combine results
				if (enabled_diffuse_map) {
					ambient = light.ambient * vec3(texture2D(diffuse_map, UV));
					diffuse = light.diffuse * diff * vec3(texture2D(diffuse_map, UV));
				} else {
					ambient = light.ambient * vec3(ambient_color);
					diffuse = light.diffuse * diff * vec3(diffuse_color);
				}
				if (enabled_specular_map) {
					specular = light.specular * spec * vec3(texture2D(specular_map, UV));
				} else {
					specular = light.specular * spec * vec3(specular_color);
				}

				return (ambient + diffuse + specular);
			}

			vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {

				vec3 lightDir = normalize(light.position - fragPos);

				// diffuse shading
				float diff = max(dot(normal, lightDir), 0.0);

				// specular shading
				vec3 reflectDir = reflect(-lightDir, normal);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

				// attenuation
				float distance = length(light.position - fragPos);
				float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

				vec3 ambient, diffuse, specular;

				// combine results
				if (enabled_diffuse_map) {
					ambient = light.ambient * vec3(texture2D(diffuse_map, UV));
					diffuse = light.diffuse * diff * vec3(texture2D(diffuse_map, UV));
				} else {
					ambient = light.ambient * vec3(ambient_color);
					diffuse = light.diffuse * diff * vec3(diffuse_color);
				}
				if (enabled_specular_map) {
					specular = light.specular * spec * vec3(texture2D(specular_map, UV));
				} else {
					specular = light.specular * spec * vec3(specular_color);
				}

				ambient  *= attenuation;
				diffuse  *= attenuation;
				specular *= attenuation;

				return (ambient + diffuse + specular);
			}

		)glsl";
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
