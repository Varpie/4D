// No copyrights, it's free.

#include "../headers/Main.h"
#include <glm/glm.hpp>
#include <string>
#include <fstream>

std::string LoadShaderFile(std::string strFile) {
	// Open the file passed in
	std::ifstream fin(strFile.c_str());

	// Make sure we opened the file correctly
	if ( !fin ) {
		return "";
	}

	std::string strLine = "";
	std::string strText = "";

	// Go through and store each line in the text file within a "string" object
	while (getline(fin, strLine)) {
		strText = strText + "\n" + strLine;
	}

	// Close our file
	fin.close();

	// Return the text file's data
	return strText;
}

void init(std::string strVertexFile, std::string strFragmentFile) {
	SDL_Init(SDL_INIT_VIDEO);

	// Will use OpenGL 4.4

	// Creating window
	window = SDL_CreateWindow("4D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

	// Setting GL context
	context = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	// Initializing GLEW.
	glewExperimental = GL_TRUE;
	glewInit();
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Making sure everything went fine, vertexBuffer will be at 1.
	// GLuint vertexBuffer;
	GLuint vbo;
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

	GLuint shaderProgram = glCreateProgram();
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
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void close() {
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}


int main(int argc, char const *argv[]) {
	// First, we initiallize our stuff.
	init("../shaders/shader.vertex", "../shaders/shader.fragment");


	// Creating event. It's what will hold the window.
	SDL_Event windowEvent;
	while (true) {
    	if (SDL_PollEvent(&windowEvent)) {
    	    if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)) break;
    	}
    	// now you can make GL calls.
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    	// SwapWindow will pass GL context to window.
		SDL_GL_SwapWindow(window);
	}

	// Break has been called, let's close everything.
	close();
	return 0;
}
