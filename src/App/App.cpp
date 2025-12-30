
#include <App.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

void App::Initialize()
{
	// Intialize video and return false if fails.
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Quit();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	// draw to a back buffer, then swap
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// needed for 3D depth testing
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_Width = 800;
	m_Height = 600;

	// SDL_WINDOW_OPENGL means this window will be used to attach an OpenGL context
	m_Window = SDL_CreateWindow("ComputeShaders", m_Width, m_Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

	if (m_Window == nullptr)
	{
		SDL_Quit();
	}

	// Load context, a state machine living inside the GPU driver, like a personal instance of OpenGL.
	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (!m_GLContext)
	{
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	if (!gladLoadGL())
	{
		SDL_GL_DestroyContext(m_GLContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForOpenGL(m_Window, m_GLContext);
	ImGui_ImplOpenGL3_Init("#version 460");

	Loop();
}

void App::Loop()
{
	bool m_bMouseCaptured = false;
	float mouseDX = 0.0f;
	float mouseDY = 0.0f;

	m_bRunning = true;

	// Frame rate limiting (60 FPS)
	const double TargetFrameTime = 1.0 / 60.0; // 60 FPS
	Uint64 FrameStartTime = SDL_GetPerformanceCounter();
	
	while (m_bRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			ImGui_ImplSDL3_ProcessEvent(&e);

			ProcessInput(&e);
		}

		static Uint64 last = SDL_GetPerformanceCounter();
		Uint64 now = SDL_GetPerformanceCounter();
		double freq = (double)SDL_GetPerformanceFrequency();
		float dt = (float)((now - last) / freq);
		last = now;

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		// App's Draw
		Draw();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);

		// ImGui UI
		{
			ImGuiIO& ImGuiIo = ImGui::GetIO();
			
			ImGui::Begin("Info");
			ImGui::Text("FPS: %.1f", ImGuiIo.Framerate);
			ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGuiIo.Framerate);
			
			ImGui::End();
		}

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(m_Window);
		
		// Frame rate limiting (60 FPS)
		Uint64 FrameEndTime = SDL_GetPerformanceCounter();
		double FrameElapsed = (double)(FrameEndTime - FrameStartTime) / (double)SDL_GetPerformanceFrequency();
		double SleepTime = TargetFrameTime - FrameElapsed;
		if (SleepTime > 0.0)
		{
			SDL_Delay((Uint32)(SleepTime * 1000.0));
		}
		FrameStartTime = SDL_GetPerformanceCounter();
	}

	Shutdown();
}

void App::Shutdown()
{
	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DestroyContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void App::ProcessInput(SDL_Event* Event)
{
	// Pressing X on the windows App
	if (Event->type == SDL_EVENT_QUIT)
	{
		m_bRunning = false;
	}

	// Pressing Esc
	if (Event->type == SDL_EVENT_KEY_DOWN)
	{
		if (Event->key.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_bRunning = false;
		}
	}

	// Support window resize
	if (Event->type == SDL_EVENT_WINDOW_RESIZED)
	{
		m_Width = Event->window.data1;
		m_Height = Event->window.data2;
	}

	// Q to capture mouse 
	if (Event->type == SDL_EVENT_KEY_DOWN && Event->key.scancode == SDL_SCANCODE_Q)
	{
		m_bMouseCaptured = !m_bMouseCaptured;
		SDL_SetWindowRelativeMouseMode(m_Window, m_bMouseCaptured ? true : false);
	}

	if (Event->type == SDL_EVENT_MOUSE_MOTION && m_bMouseCaptured) {
		m_MouseX += (float)Event->motion.xrel;
		m_MouseY += (float)Event->motion.yrel;
	}
}

void App::Draw()
{


}

