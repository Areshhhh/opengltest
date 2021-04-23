#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui\imgui.h"



namespace test {

	TestClearColor::TestClearColor() : m_ClearColor{ 0.3f, 0.1f, 0.3f, 1.0f }
	{}
	TestClearColor::~TestClearColor()
	{}



	void TestClearColor::onUpdate(float deltaTime)
	{}
	void TestClearColor::onOpenglRender()
	{
		renderer.ClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	}
	void TestClearColor::onImguiRender()
	{
		ImGui::ColorEdit4("clear color", m_ClearColor);
	}

}