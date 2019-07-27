#include "egpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>




namespace Engine
{
	Application::Application()
	{
		EG_CORE_WARN("Engine Statically Linked!");
		m_Window = std::unique_ptr<Window>(Window::Create());

		unsigned int id;
		glGenVertexArrays(1,&id);
		
		EG_CORE_INFO("VertexArray: {0}", id);

	

	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		/*
		WindowResizeEvent e(1280, 720);
		KeyPressedEvent k_e(65, 1);
		if (e.IsInCategory(EventCategoryApplication))
		{
			EG_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			EG_TRACE(e);
		}
		EG_TRACE(k_e);
		//EG_CORE_WARN("Initialized Log!");
		EG_ERROR("FATAL from APP!");
		int i = 10;
		EG_ERROR("Var = {0}", i);
	*/

		while (m_Running)
		{
			/*
		
			
			*/
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
			
			
		}	
	}
}