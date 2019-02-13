#pragma once

#include <glm/glm.hpp>

#include "object.h"
#include "color.h"
#include "texture.h"
#include "shader.h"

namespace se {

	class Material : public Object	{

		public:
			Material();
			~Material();

			Color color; // The main material's color.
			//doubleSidedGI; // Gets and sets whether the Double Sided Global Illumination setting is enabled for this material.
			//enableInstancing; // Gets and sets whether GPU instancing is enabled for this material.
			//globalIlluminationFlags; // Defines how the material should interact with lightmaps and lightprobes.
			Texture* mainTexture; // The material's texture.
			glm::vec2 mainTextureOffset; // The texture offset of the main texture.
			glm::vec2 mainTextureScale; // The texture scale of the main texture.
			//passCount; // How many passes are in this material (Read Only).
			//renderQueue; // Render queue of this material.
			Shader* shader; // The shader used by the material.
			//string shaderKeywords[]; // Additional shader keywords set by this material.

			// methods

			//void CopyPropertiesFromMaterial(Material*); // Copy properties from other material into this material.
			//void DisableKeyword(string); // Unset a shader keyword.
			//void EnableKeyword(string); // Sets a shader keyword that is enabled by this material.
			////FindPass(); // Returns the index of the pass passName.
			//void GetColor(); // Get a named color value.
			//void GetColorArray(); // Get a named color array.
			//void GetFloat(); // Get a named float value.
			//void GetFloatArray(); // Get a named float array.
			//void GetInt(); // Get a named integer value.
			//void GetMatrix(); // Get a named matrix value from the shader.
			//void GetMatrixArray(); // Get a named matrix array.
			//void GetPassName(); // Returns the name of the shader pass at index pass.
			//void GetShaderPassEnabled(); // Checks whether a given Shader pass is enabled on this Material.
			//void GetTag(); // Get the value of material's shader tag.
			//void GetTexture(); // Get a named texture.
			//void GetTextureOffset(); // Gets the placement offset of texture propertyName.
			//void GetTextureScale(); // Gets the placement scale of texture propertyName.
			//void GetVector(); // Get a named vector value.
			//void GetVectorArray(); // Get a named vector array.
			//void HasProperty(); // Checks if material's shader has a property of a given name.
			//void IsKeywordEnabled(); // Is the shader keyword enabled on this material?
			//void Lerp(); // Interpolate properties between two materials.
			//void SetBuffer(); // Sets a named ComputeBuffer value.
			//void SetColor(); // Sets a named color value.
			//void SetColorArray(); // Sets a color array property.
			//void SetFloat(); // Sets a named float value.
			//void SetFloatArray(); // Sets a float array property.
			//void SetInt(); // Sets a named integer value.
			//void SetMatrix(); // Sets a named matrix for the shader.
			//void SetMatrixArray(); // Sets a matrix array property.
			//void SetOverrideTag(); // Sets an override tag/value on the material.
			//void SetPass(); // Activate the given pass for rendering.
			//void SetShaderPassEnabled(); // Enables or disables a Shader pass on a per-Material level.
			//void SetTexture(); // Sets a named texture.
			//void SetTextureOffset(); // Sets the placement offset of texture propertyName.
			//void SetTextureScale(); // Sets the placement scale of texture propertyName.
			//void SetVector(); // Sets a named vector value.
			//void SetVectorArray(); // Sets a vector array property.

		protected:

		private:
	};

}
