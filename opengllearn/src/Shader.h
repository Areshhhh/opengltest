#pragma once

#include "glm\glm.hpp"
#include <tuple>
#include <string>

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void Setuniform1i(const std::string& name, int value);
	void Setuniform1f(const std::string& name, float value);
	void Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetuniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};