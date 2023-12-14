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
        std::cerr << "One or more shaders failed, exiting..." << std::endl;
        return 0;
    }

    GLuint program = compileAndLinkProgram(vertexShader, fragmentShader);

    // after the program has been compiled and linked the individual shaders can be released
    glDeleteShader(vertexShader);
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glDeleteShader1 failed with error: " << err << std::endl;
    }

    glDeleteShader(fragmentShader);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glDeleteShader2 failed with error: " << err << std::endl;
    }

    return program;
}


GLuint ShaderUtil::loadShader (const std::string& a_shaderPath, GLenum a_shaderType) {
    // Open the source path
    std::ifstream sourceFile(a_shaderPath.c_str());
    if (!sourceFile) {
        std::cerr << "Could not read shader file `" << a_shaderPath << "`" << std::endl;
        return 0;
    }

    // Read the whole file into a string
    std::string source = std::string((std::istreambuf_iterator<char>(sourceFile)),
        std::istreambuf_iterator<char>());
    sourceFile.close();

    // Create a shader and test successful creation
    GLuint shaderHandle = glCreateShader(a_shaderType);
    if (shaderHandle == 0) {
        std::cerr << "Shader creation failed" << std::endl;
        return 0;
    }

    // Load sourcePointer (which is one string) into shaderHandle, and since its null terminated we can
    // pass in NULL for the length array
    const char* sourcePointer = source.c_str();
    glShaderSource(shaderHandle, 1, &sourcePointer, NULL);

    // compile and check compilation status
    glCompileShader(shaderHandle);
    
    GLint compileStatus = 0;

    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        std::cerr << "Shader compilation failed:" << std::endl;

        GLint logLength = 0;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar* errorLog = new GLchar[logLength];
            glGetShaderInfoLog(shaderHandle, logLength, NULL, errorLog);
            std::cerr << errorLog << std::endl;
            delete[] errorLog;
        }
        else {
            std::cerr << "No info available." << std::endl;
        }
        return 0;
    }

    //std::cout << "Shader: " << a_shaderPath << " compiled successfuly." << std::endl;
    return shaderHandle;
}

/**
 * Take the given shaders and link them into a new program
 */
GLuint ShaderUtil::compileAndLinkProgram (const GLuint a_vertexShaderHandle, const GLuint a_fragmentShaderHandle) {

    GLuint program = glCreateProgram();
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glCreateProgram failed with error: " << err << std::endl;
    }

    glAttachShader(program, a_vertexShaderHandle);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glAttachShader1 failed with error: " << err << std::endl;
    }

    glAttachShader(program, a_fragmentShaderHandle);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glAttachShader2 failed with error: " << err << std::endl;
    }

    glLinkProgram(program);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glLinkProgram failed with error: " << err << std::endl;
    }

    int linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        std::cerr << "Linking failed... " << std::endl;

        int linkLogSize = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &linkLogSize);

        GLchar* linkLog = new GLchar[linkLogSize];
        glGetProgramInfoLog(program, linkLogSize, NULL, linkLog);
        std::cerr << linkLog << std::endl;
        delete[] linkLog;
        return 0;
    }

    // detach the shaders again (there is a binary linked program now)
    glDetachShader(program, a_vertexShaderHandle);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glDetachShader1 failed with error: " << err << std::endl;
    }

    glDetachShader(program, a_fragmentShaderHandle);
    err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "glDetachShader2 failed with error: " << err << std::endl;
    }

    return program;
}

