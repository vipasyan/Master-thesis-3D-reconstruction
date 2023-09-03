#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
    : mHandle(0)
{
}

Shader::~Shader()
{
    // Delete the program
    glDeleteProgram(mHandle);
}

bool Shader::loadShaders(const char *vsFilename, const char *fsFilename)
{
    string vsString = fileToString(vsFilename);
    string fsString = fileToString(fsFilename);
    const GLchar *vsSourcePtr = vsString.c_str();
    const GLchar *fsSourcePtr = fsString.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSourcePtr, NULL);
    glShaderSource(fs, 1, &fsSourcePtr, NULL);

    glCompileShader(vs);
    checkCompileErrors(vs, VERTEX);

    glCompileShader(fs);
    checkCompileErrors(fs, FRAGMENT);

    mHandle = glCreateProgram();
    if (mHandle == 0)
    {
        std::cerr << "Unable to create shader program!" << std::endl;
        return false;
    }

    glAttachShader(mHandle, vs);
    glAttachShader(mHandle, fs);

    glLinkProgram(mHandle);
    checkCompileErrors(mHandle, PROGRAM);

    glDeleteShader(vs);
    glDeleteShader(fs);

    mUniformLocations.clear();

    return true;
}

string Shader::fileToString(const string &filename)
{
    std::stringstream ss;
    std::ifstream file;

    // Enable ifstream object exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(filename, std::ios::in);

        if (!file.fail())
        {
            ss << file.rdbuf();
        }

        file.close();
    }
    catch (std::exception ex)
    {
        std::cerr << "Error reading shader file " << filename << std::endl;
    }

    return ss.str();
}

void Shader::use()
{
    if (mHandle > 0)
        glUseProgram(mHandle);
}

void Shader::checkCompileErrors(GLuint shader, ShaderType type)
{
    int status = 0;

    if (type == PROGRAM)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint length = 0;
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

            // The length includes the NULL character
            string errorLog(length, ' '); // Resize and fill with space character
            glGetProgramInfoLog(shader, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader program failed to link. " << errorLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            // The length includes the NULL character
            string errorLog(length, ' '); // Resize and fill with space character
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader failed to compile. " << errorLog << std::endl;
        }
    }
}

GLuint Shader::getProgram() const
{
    return mHandle;
}

void Shader::setUniform(const GLchar *name, const glm::vec2 &v)
{
    GLint loc = getUniformLocation(name);
    glUniform2f(loc, v.x, v.y);
}

void Shader::setUniform(const GLchar *name, const glm::vec3 &v)
{
    GLint loc = getUniformLocation(name);
    glUniform3f(loc, v.x, v.y, v.z);
}

void Shader::setUniform(const GLchar *name, const glm::vec4 &v)
{
    GLint loc = getUniformLocation(name);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void Shader::setUniform(const GLchar *name, const glm::mat4 &m)
{
    GLint loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setUniform(const GLchar *name, const GLfloat f)
{
    GLint loc = getUniformLocation(name);
    glUniform1f(loc, f);
}

void Shader::setUniform(const GLchar *name, const GLint v)
{
    GLint loc = getUniformLocation(name);
    glUniform1i(loc, v);
}

void Shader::setUniformSampler(const GLchar *name, const GLint &slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);

    GLint loc = getUniformLocation(name);
    glUniform1i(loc, slot);
}

GLint Shader::getUniformLocation(const GLchar *name)
{
    std::map<string, GLint>::iterator it = mUniformLocations.find(name);

    // Only need to query the shader program IF it doesn't already exist.
    if (it == mUniformLocations.end())
    {
        // Find it and add it to the map
        mUniformLocations[name] = glGetUniformLocation(mHandle, name);
    }

    // Return it
    return mUniformLocations[name];
}