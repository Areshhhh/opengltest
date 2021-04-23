#pragma once
#include "Renderer.h"

namespace test {

	class Test
	{
	public:
		Renderer renderer;

		Test() {}
		virtual ~Test() {}
	
		virtual void onUpdate(float deltaTime) {}
		virtual void onOpenglRender()		   {}
		virtual void onImguiRender()		   {}
	};

}