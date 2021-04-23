#pragma once

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"



namespace test {

	class TestCube : Test
	{
	public:
		 TestCube();
		~TestCube();

		void updatePositons(int x, int y);
		void onUpdate(float deltaTime) override;
		void onOpenglRender() override;
		void onImguiRender()  override;

	private:
		VertexBuffer vb;
		VertexArray  va;
		IndexBuffer  ib;
		Shader   shader;
		Texture texture;
		VertexBufferLayout layout;
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		glm::mat4 mvp;
	};

}