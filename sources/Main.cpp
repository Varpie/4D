// No copyrights, it's free.

#include "../headers/Main.h"

Model model;
Renderer renderer;

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