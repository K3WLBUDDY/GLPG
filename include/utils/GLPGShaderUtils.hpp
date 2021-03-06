#pragma once
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>
#include <vector>

#include "../internal/GLPGContextImpl_GL.hpp"

namespace GLPG {

    bool CheckGLError() {
        bool ret = true;
        if (GLenum error = glGetError(); error != GL_NO_ERROR) {
            std::cerr << "GLPG GL Error: " << std::hex << error << std::dec << "\n";
            ret = false;
        }

        return ret;
    }

    bool compileShader(int shaderObject, const char *shaderSource) {
        int success = GL_FALSE;
        glShaderSource(shaderObject, 1, &shaderSource, nullptr);
        glCompileShader(shaderObject);
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

        if (success != GL_TRUE) {
            int shaderType;
            int maxLength = 0;
            glGetShaderiv(shaderObject, GL_SHADER_TYPE, &shaderType);
            std::cout << "Shader compilation of type " << shaderType << " Failed!!"
                      << std::endl;
            glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shaderObject, maxLength, &maxLength, &errorLog[0]);
            glDeleteShader(shaderObject);
            std::string s(errorLog.begin(), errorLog.end());
            std::cout << "Compilation Log: " << s << std::endl;

            return false;
        }
        return true;
    }

    bool linkShaders(int programObject) {
        int success = GL_FALSE;
        glLinkProgram(programObject);
        glGetProgramiv(programObject, GL_LINK_STATUS, &success);

        if (success != GL_TRUE) {
            int maxLength = 0;
            std::cout << "Shader Linking Failed !!" << std::endl;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(programObject, maxLength, &maxLength, &errorLog[0]);

            std::string s(errorLog.begin(), errorLog.end());
            std::cout << "Link Log : " << s << std::endl;
            return false;
        }
        return true;
    }
} // namespace GLPG
