#pragma once

#ifdef CF_PLATFORM_WINDOWS

extern CFrame::Application* CFrame::CreateApplication();

int main(int argc, char** argv)
{
	CFrame::Log::Init();
	CF_CORE_WARN("Initialized Log!!");
	CF_INFO("Hello!");

	auto app = CFrame::CreateApplication();
	app->run();
	delete app;
}

#else
	#error CFrame only supports Windows!
#endif