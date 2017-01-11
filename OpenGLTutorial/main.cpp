#include <GL\glew.h>

#include <iostream>
#include "display.h"

using namespace std;

int main(int argc, char** argv) {
	Display display(600, 800, "Hello World");

	while (!display.isClosed()) {
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		display.update();
	}

	return 0;
}