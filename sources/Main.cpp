// No copyrights, it's free.

#include "../headers/Main.h"

Model model;
Renderer renderer;

void printSDL_GL_Attributes();
void checkSDLError(int line);


/*

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Making sure everything went fine, vertexBuffer will be at 1.
	// GLuint vertexBuffer;
	glGenBuffers(1, &vbo);  // Generate 1 buffer
	// glGenBuffers(1, &vertexBuffer);
	GLfloat vertices[] = {
		0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glm::vec2 position = glm::vec2(0.0, 0.0);
	glm::vec4 gl_Position = glm::vec4(position, 0.0, 1.0);
	glm::vec4 outColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	// Compiling shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertexSource = LoadShaderFile(strVertexFile).c_str();
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource = LoadShaderFile(strFragmentFile).c_str();
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));*/


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

		renderer.render();
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
