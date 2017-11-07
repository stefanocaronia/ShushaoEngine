#pragma once

#include "object.h"
#include "shaderprogram.h"

namespace ShushaoEngine {

	enum ShaderLocation {
		POSITION = 0,
		TEXCOORD = 1
	};

	class Shader : public Object, public ShaderProgram {

		public:

			Shader();

			//static void DisableKeyword(); // Unset a global shader keyword.
			//static void EnableKeyword(); // Set a global shader keyword.
			//static void Find(); // Finds a shader with the given name.
			//static void GetGlobalColor(); // Gets a global color property for all shaders previously set using SetGlobalColor.
			//static void GetGlobalFloat(); // Gets a global float property for all shaders previously set using SetGlobalFloat.
			//static void GetGlobalFloatArray(); // Gets a global float array for all shaders previously set using SetGlobalFloatArray.
			//static void GetGlobalInt(); // Gets a global int property for all shaders previously set using SetGlobalInt.
			//static void GetGlobalMatrix(); // Gets a global matrix property for all shaders previously set using SetGlobalMatrix.
			//static void GetGlobalMatrixArray(); // Gets a global matrix array for all shaders previously set using SetGlobalMatrixArray.
			//static void GetGlobalTexture(); // Gets a global texture property for all shaders previously set using SetGlobalTexture.
			//static void GetGlobalVector(); // Gets a global vector property for all shaders previously set using SetGlobalVector.
			//static void GetGlobalVectorArray(); // Gets a global vector array for all shaders previously set using SetGlobalVectorArray.
			//static void IsKeywordEnabled(); // Is global shader keyword enabled?
			//static void PropertyToID(); // Gets unique identifier for a shader property name.
			//static void SetGlobalBuffer(); // Sets a global compute buffer property for all shaders.
			//static void SetGlobalColor(); // Sets a global color property for all shaders.
			//static void SetGlobalFloat(); // Sets a global float property for all shaders.
			//static void SetGlobalFloatArray(); // Sets a global float array property for all shaders.
			//static void SetGlobalInt(); // Sets a global int property for all shaders.
			//static void SetGlobalMatrix(); // Sets a global matrix property for all shaders.
			//static void SetGlobalMatrixArray(); // Sets a global matrix array property for all shaders.
			//static void SetGlobalTexture(); // Sets a global texture property for all shaders.
			//static void SetGlobalVector(); // Sets a global vector property for all shaders.
			//static void SetGlobalVectorArray(); // Sets a global vector array property for all shaders.
			//static void WarmupAllShaders(); // Fully load all shaders to prevent future performance hiccups.

		protected:

		private:
	};

}
