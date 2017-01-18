#pragma once

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Display::clear(float r, float g, float b, float a);
	void Display::update();
	bool Display::isClosed();

	virtual ~Display();
private:
	Display(const Display& other) {}
	Display& operator=(const Display& other) {}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed;
};

