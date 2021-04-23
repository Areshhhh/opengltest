#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[opengl error] (" << error << "): " << function << " " << file << ":"
			<< line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sh) const
{
	va.Bind();
	ib.Bind(); //binding vertex array and index buffer
	sh.Bind(); //shader binding and color changing setting
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
	GLCall(glClearColor(r, g, b, a));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}