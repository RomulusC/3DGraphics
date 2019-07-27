#include "egpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Engine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) 
	Application::Application()
	{
		EG_CORE_WARN("Engine Statically Linked!");
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
	

	}
	Application::~Application()
	{

	}
	
		
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		EG_CORE_TRACE("{0}",e);		
	}
	void Application::Run()
	{
		while (m_Running)
		{			
			glClearColor(.1f, .1f, .1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();			
		}	
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}