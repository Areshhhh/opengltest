#include "TestCube.h"



namespace test {

	float vertexPositions[] =
	{
		000.0f,	000.0f,    0.0f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
		050.0f,	000.0f,    0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
		050.0f,	100.0f,    0.5f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
		000.0f, 100.0f,    0.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,

		050.0f,	000.0f,    0.5f, 0.0f,     0.0f, 0.3f, 1.0f, 1.0f,
		100.0f,	000.0f,    1.0f, 0.0f,     0.0f, 0.3f, 1.0f, 1.0f,
		100.0f,	100.0f,    1.0f, 1.0f,     0.0f, 1.0f, 1.0f, 1.0f,
		050.0f, 100.0f,    0.5f, 1.0f,     0.0f, 0.3f, 1.0f, 1.0f
	};

	unsigned int indexPositions[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4
	};



	TestCube::TestCube()
		: vb(vertexPositions, 8 * 8 * sizeof(float)),
		  layout(),
		  va(),
		  ib(indexPositions, 12),
		  shader("res/shaders/basic.shader"),
		  texture("res/textures/basic.png"),
		  proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
		  model(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		  view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		  mvp(proj * view * model)
	{
		
		layout.push<float>(2);
		layout.push<float>(2);
		layout.push<float>(4);

		va.Bind();
		va.addbuffer(vb, layout);

		shader.Bind();
		shader.Setuniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		shader.SetuniformMat4f("u_MVP", mvp);

		texture.Bind();
		shader.Setuniform1i("u_Texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

	}

	TestCube::~TestCube()
	{}


	void TestCube::updatePositons(int x, int y)
	{
		shader.Bind();
		view = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
		mvp = proj * view * model;
		shader.SetuniformMat4f("u_MVP", mvp);
		shader.Unbind();
	}

	void TestCube::onUpdate(float deltaTime)
	{}

	void TestCube::onOpenglRender()
	{
		renderer.Draw(va, ib, shader);
	}

	void TestCube::onImguiRender()
	{}

}