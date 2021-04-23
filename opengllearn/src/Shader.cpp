#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
    auto [VertexSource, FragmentSource] = ParseShader(filepath);
    m_RendererID = CreateShader(VertexSource, FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile shader\n" << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::Setuniform1i(const std::string& name, int value)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "uniform '" << name << "' not found." << std::endl;
    GLCall(glUniform1i(location, value));
}

void Shader::Setuniform1f(const std::string& name, float value)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "uniform '" << name << "' not found." << std::endl;
    GLCall(glUniform1f(location, value));
}

void Shader::Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "uniform '" << name << "' not found." << std::endl;
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetuniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "uniform '" << name << "' not found." << std::endl;
    GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}