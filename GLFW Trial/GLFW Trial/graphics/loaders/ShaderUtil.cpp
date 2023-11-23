#include "ShaderUtil.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string ShaderUtil::createString(const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath)
{
    return a_vertexShaderPath + '\t' + a_fragmentShaderPath;
}

GLuint ShaderUtil::createProgram(const std::string& a_vertex_fragment_Shaderpath)
{
    std::stringstream stream(a_vertex_fragment_Shaderpath);

    std::string vertexPath;
    std::getline(stream, vertexPath, '\t');
    std::string fragmentPath;
    std::getline(stream, fragmentPath, '\t');

    return createProgram(vertexPath, fragmentPath);
}

GLuint ShaderUtil::createProgram (const std::string& a_vertexShaderPath, const std::string& a_fragmentShaderPath)
{
    GLuint vertexShader = loadShader(a_vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader(a_fragmentShaderPath, GL_FRAGMENT_SHADER);

    if (vertexShader == 0 || fragmentShader == 0) {
        std::cout << "One or more shaders failed, exiting..." << std::endl;
        return 0;
    }

    std::vector<GLuint> shaders;
    shaders.push_back(vertexShader);
    shaders.push_back(fragmentShader);

    GLuint program = compileAndLinkProgram(shaders);

    //after the program has been compiled and linked we can release the individual shaders
    for (size_t i = 0; i < shaders.size(); i++) {
        glDeleteShader(shaders[i]);
    }

    return program;
}


GLuint ShaderUtil::loadShader (const std::string& pShaderPath, GLenum pShaderType) {
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Loading file " << pShaderPath << ":" << std::endl << std::endl;

    //open the source path
    std::ifstream sourceFile(pShaderPath.c_str());
    if (!sourceFile) {
        std::cout << "Could not read shader file <" << pShaderPath << ">";
        std::cout << "-----------------------------------" << std::endl;
        return 0;
    }

    //read the whole file into a stream
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    sourceFile.close();

    //dump source on the output stream so we can see it
    std::string source = buffer.str();
    std::cout << source;
    std::cout << "-----------------------------------" << std::endl;

    //create a shader and test successful creation
    std::cout << "Creating shader object..." << std::endl;
    GLuint shaderHandle = glCreateShader(pShaderType);
    std::cout << "Shader creation successful? " << (shaderHandle != 0 ? "Yes" : "No") << std::endl;
    if (shaderHandle == 0) return 0;

    //load sourcePointer (which is one string) into shaderHandle, and since its null terminated we can
    //pass in NULL for the length array
    std::cout << "Loading source into shader..." << std::endl;
    char const* sourcePointer = source.c_str();
    glShaderSource(shaderHandle, 1, &sourcePointer, NULL);

    //compile and check compilation status
    std::cout << "Compiling shader..." << std::endl;
    glCompileShader(shaderHandle);
    GLint compileStatus = 0;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        std::cout << "Shader compilation failed:" << std::endl;

        GLint logLength = 0;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar* errorLog = new GLchar[logLength];
            glGetShaderInfoLog(shaderHandle, logLength, NULL, errorLog);
            std::cout << errorLog << std::endl;
            delete[] errorLog;
        }
        else {
            std::cout << "No info available." << std::endl;
        }
        return 0;
    }

    std::cout << "Shader compilation successful." << std::endl << std::endl;
    return shaderHandle;
}

/**
 * Take the given list of shaders and link them into a new program
 */
GLuint ShaderUtil::compileAndLinkProgram (const std::vector<GLuint> &pShaders) {
    std::cout << "Creating new program..." << std::endl;
    GLuint program = glCreateProgram();
    std::cout << "Program id:" << program << std::endl;
    for (size_t i = 0; i < pShaders.size(); i++) {
        std::cout << "   Attaching shader " << pShaders[i] << std::endl;
        glAttachShader(program, pShaders[i]);
    }
    std::cout << "Linking program..." << std::endl;
    glLinkProgram(program);

    int linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        std::cout << "Linking failed... " << std::endl;

        int linkLogSize = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &linkLogSize);

        GLchar* linkLog = new GLchar[linkLogSize];
        glGetProgramInfoLog(program, linkLogSize, NULL, linkLog);
        std::cout << linkLog << std::endl;
        delete[] linkLog;
        return 0;

    }
    else {
        std::cout << "Link successful." << std::endl;
    }

    std::cout << std::endl;

    //detach the shaders again (we have a binary linked program now)
    for (size_t i = 0; i < pShaders.size(); i++) {
        glDetachShader(program, pShaders[i]);
    }

    return program;
}

