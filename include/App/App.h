#pragma once

#include <SDL3/SDL.h>

/**
 * App
 * 
 * Main application class that manages the application lifecycle.
 * Uses SDL3 to create a window, initialize OpenGL context, and handle input events.
 */
class App
{
public:

	App() {}
	~App() {}
	 
	/* Initializes the application and calls Loop to start the core game loop. */
	void Initialize();

protected:
	/* Core loop. */
	void Loop();

	/* Shutdown proccess. */
	void Shutdown();

	void ProcessInput(SDL_Event* Event);
	
	/* Called each frame just before we clear the screen. Place here draw calls. */
	void Draw();

private:
	SDL_Window* m_Window = nullptr;
	SDL_GLContext m_GLContext = nullptr;

	int m_Width = 800;
	int m_Height = 600;

	bool m_bMouseCaptured = false;
	bool m_bRunning = false;

	float m_MouseX = 0.f;
	float m_MouseY = 0.f;
};
