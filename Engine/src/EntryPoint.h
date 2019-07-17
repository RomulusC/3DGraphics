#pragma once


#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EG_CORE_WARN("Initialized Log!");
	EG_ERROR("FATAL from APP!");
	int i = 10;
	EG_ERROR("Var = {0}", i);
	


	printf("Engine Dynamically Linked!\n");
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#endif // EG_PLATFORM_WINDOWS
