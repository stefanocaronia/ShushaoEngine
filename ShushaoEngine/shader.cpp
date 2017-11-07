#include "shader.h"

#include <fstream>

namespace ShushaoEngine {

	Shader::Shader() {
        // default shaders for sprite rendering
        /*VertexShaderCode =
        #include "standard.vert"
        ;

        FragmentShaderCode =
		#include "standard.frag"
        ;*/
		cout << "[] Shader Constructor" << endl;
		name = "Shader";

        load("standard");
	}

}
