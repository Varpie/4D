// No copyrights, it's free.

#include "../headers/Main.h"

Model model;
Renderer renderer;

void printSDL_GL_Attributes();
void checkSDLError(int line);


int main(int argc, char const *argv[]) {
	// First, we initiallize our stuff.
	renderer.init(/*"../shaders/shader.vertex", "../shaders/shader.fragment"*/);
	model.setupBufferObjects();


	// Creating event. It's what will hold the window.
	SDL_Event windowEvent;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)) break;
		}
    	// now you can make GL calls.

		renderer.render(model.getModel());
	}

	// Break has been called, let's close everything.
	renderer.close();
	return 0;
}

void checkSDLError(int line = -1) {
	std::string error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

void printSDL_GL_Attributes() {
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
