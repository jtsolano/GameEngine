
#include <App.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

#include <Program.h>
#include <Mesh.h>
#include <Texture.h>
#include <Color.h>
#include <PrimitiveMeshBuilder.h>

#include <glm/gtc/matrix_transform.hpp> // lookAt, perspective
#include <glm/gtc/type_ptr.hpp>

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

	SetupScene();

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

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Frame rate limiting (60 FPS)
		Uint64 FrameEndTime = SDL_GetPerformanceCounter();
		double FrameElapsed = (double)(FrameEndTime - FrameStartTime) / (double)SDL_GetPerformanceFrequency();
		double SleepTime = TargetFrameTime - FrameElapsed;
		if (SleepTime > 0.0)
		{
			SDL_Delay((Uint32)(SleepTime * 1000.0));
		}
		FrameStartTime = SDL_GetPerformanceCounter();

		// App's Draw
		Draw(TargetFrameTime);

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

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

		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 100.0f);
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

void App::SetupScene()
{
	// Setup projection matrix.
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 100.0f);

	if(true)
	{
		shared_ptr<Drawable> Quad1 = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/basic.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		Quad1->m_Program->AddShader(ShaderSource.c_str());
		Quad1->m_Program->Compile();
		Quad1->m_Mesh = PrimitiveMeshBuilder::BuildQuad(0.25f);
		Quad1->Translate(glm::vec3(-1.5f, 0.0f, 0.0f));
		m_Drawables.push_back(Quad1);
	}

	if (true)
	{
		shared_ptr<Drawable> Quad2 = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/basic_color.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		Quad2->m_Program->AddShader(ShaderSource.c_str());
		Quad2->m_Program->Compile();
		Quad2->m_Mesh = PrimitiveMeshBuilder::BuildQuad(0.5f, Colors::Blue);
		Quad2->Translate(glm::vec3(1.0f, 0.0f, 0.0f));
		m_Drawables.push_back(Quad2);
	}

	if (true)
	{
		shared_ptr<Drawable> Quad3 = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/basic_texture.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		Quad3->m_Program->AddShader(ShaderSource.c_str());
		Quad3->m_Program->Compile();
		Quad3->m_Mesh = PrimitiveMeshBuilder::BuildQuadTexture(0.5f);
		Quad3->Translate(glm::vec3(0.0f, 1.0f, 0.0f));
		m_Drawables.push_back(Quad3);
	}

	if(false)
	{
		shared_ptr<Drawable> ScreenQuad = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/ray_marching_sphere.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		ScreenQuad->m_Program->AddShader(ShaderSource.c_str());
		ScreenQuad->m_Program->Compile();
		ScreenQuad->m_Mesh = PrimitiveMeshBuilder::BuildScreenQuad();
		m_Drawables.push_back(ScreenQuad);
	}

	if (true)
	{
		shared_ptr<Drawable> Cube = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/basic.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		Cube->m_Program->AddShader(ShaderSource.c_str());
		Cube->m_Program->Compile();
		Cube->m_Mesh = PrimitiveMeshBuilder::BuildCube(0.25);
		Cube->AddConstantRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Cube->AddConstantRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		Cube->Translate(glm::vec3(0.0f, -1.0f, 0.0f));
		m_Drawables.push_back(Cube);
	}

	if (true)
	{
		shared_ptr<Drawable> Cube = make_shared<Drawable>();
		string ShaderSourceFilePath = string(PROJECT_ROOT) + string("shaders/basic_texture.glsl");
		string ShaderSource = FileUtils::ReadFile(ShaderSourceFilePath.c_str());
		Cube->m_Program->AddShader(ShaderSource.c_str());
		Cube->m_Program->Compile();
		Cube->m_Mesh = PrimitiveMeshBuilder::BuildCubeTextured(0.25);
		Cube->AddConstantRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Cube->AddConstantRotation(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		Cube->Translate(glm::vec3(-1.0f, -1.0f, 0.0f));
		m_Drawables.push_back(Cube);
	}

	shared_ptr<Texture> Test = make_shared<Texture>();

	m_Textures.push_back(Test);

}

void App::Draw(float DeltaTime)
{
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm:vec2 Resolution = glm::vec2(m_Width, m_Height);

	for (shared_ptr<Drawable> Drawable : m_Drawables)
	{ 
		Drawable->Update(DeltaTime);
		Drawable->m_Program->Use();
		Drawable->m_Program->SetUniformMatrix4f("model", Drawable->GetModelMatrixPtr());
		Drawable->m_Program->SetUniformMatrix4f("view", glm::value_ptr(view));
		Drawable->m_Program->SetUniformMatrix4f("projection", glm::value_ptr(m_ProjectionMatrix));
		Drawable->m_Program->SetUniformMatrix4f("uResolution", glm::value_ptr(Resolution));
		Drawable->m_Mesh->Draw();
	}
}

