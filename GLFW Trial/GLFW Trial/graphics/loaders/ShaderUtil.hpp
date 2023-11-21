#pragma once

#include <GL/glew.h>
#include <vector>
#include <string_view>

class ShaderUtil
{
    public:
        static std::string createString(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath);
        static GLuint createProgram(const std::string& a_vertex_fragment_Shaderpath);
        static GLuint createProgram (std::string_view a_vertexShaderPath, std::string_view a_fragmentShaderPath);

    private:
        static GLuint loadShader (std::string_view pShaderPath, GLenum pShaderType);
        static GLuint compileAndLinkProgram (const std::vector<GLuint>& pShaders);
};
