// No copyrights, it's free.

#pragma once

class Renderer {
	glm::mat4 projection;
	glm::mat4 view;
	SDL_Window *window;
	SDL_GLContext context;
	Shader shader;
	
	public:

	Renderer() {
		projection = glm::perspective (
			45.0f,
			1.0f/1.0f,
			0.1f,
			100.0f
		);
		
		view = glm::lookAt(
			glm::vec3(0,0,-4),
			glm::vec3(0,0,0),
			glm::vec3(0,1,0)
		);
	}
	

	bool setOpenGlAttributes() {
		// SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		/* Turn on double buffering with a 24bit Z buffer.
		 * You may need to change this to 16 or 32 for your system */
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		return true;
	}


	bool init() {
		SDL_Init(SDL_INIT_VIDEO);

		// Will use OpenGL 4.4

		// Creating window
		window = SDL_CreateWindow("4D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

		setOpenGlAttributes();

		// Setting GL context
		context = SDL_GL_CreateContext(window);
		SDL_GL_SetSwapInterval(1); 
		
		// Initializing GLEW.
		glewExperimental = GL_TRUE;
		GLenum rev;
		rev = glewInit();

		if (GLEW_OK != rev){
			std::cout << "Error: " << glewGetErrorString(rev) << std::endl;
			exit(1);
		}

		return true;
	}

	void render(glm::mat4 model) {
		// Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
		// glDrawArrays(GL_LINE_LOOP, 0, 4);
	
		// Putting some color
		// glEnableVertexAttribArray(colorAttributeIndex);
	
		// Make our background black
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// Invoke glDrawArrays telling that our data is a triangle fan and we want to draw 2-4 vertexes
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glm::mat4 mvp = projection * view * model;
		// Swap our buffers to make our changes visible
		SDL_GL_SwapWindow(window);
	}

	void close() {
		shader.cleanUp();
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
	
		SDL_Quit();
	}
};
