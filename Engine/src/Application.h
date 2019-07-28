#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window/Windows.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
namespace Engine
{
	class Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow(){ return *m_Window; }


	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	//To be defined in client. 
	Application* CreateApplication();
}