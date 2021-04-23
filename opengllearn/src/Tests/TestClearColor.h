#pragma once

#include "Test.h"



namespace test {

	class TestClearColor : public Test
	{
	public:
		 TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onOpenglRender() override;
		void onImguiRender()  override;

	private:
		float m_ClearColor[4];
	};

}