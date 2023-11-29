#pragma once

#include <GL/glew.h>
#include <vector>
#include <string_view>

class ShaderUtil
{
    public:
        static std::string createString(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath);
        static GLuint createProgram(const std::string& a_vertex_fragment_Shaderpath);
        static GLuint createProgram(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath);

    private:
        static GLuint loadShader (const std::string& a_shaderPath, GLenum a_shaderType);
        static GLuint compileAndLinkProgram (const GLuint a_vertexShaderHandle, const GLuint a_fragmentShaderHandle);
};
