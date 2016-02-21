// No copyrights, it's free.

#include "../headers/Main.h"
#include "../headers/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <string>
#include <fstream>

// GLuint shaderProgram;
SDL_Window *window;
SDL_GLContext context;

// Our object has 4 points
const uint32_t points = 4;

// Each poin has three values ( x, y, z)
const uint32_t floatsPerPoint = 3;

// Each color has 4 values ( red, green, blue, alpha )
const uint32_t floatsPerColor = 4;

// This is the object we'll draw ( a simple square
const GLfloat diamond[points][floatsPerPoint] = {
	{ -0.5,  0.5,  0.5 }, // Top left
	{  0.5,  0.5,  0.5 }, // Top right
	{  0.5, -0.5,  0.5 }, // Bottom right 
	{ -0.5, -0.5,  0.5 }, // Bottom left
};

// This is the object we'll draw ( a simple square
const GLfloat colors[points][floatsPerColor] = {
	{ 0.0, 1.0, 0.0, 1.0 }, // Top left
	{ 1.0, 1.0, 0.0, 1.0  }, // Top right
	{ 1.0, 0.0, 0.0, 1.0  }, // Bottom right 
	{ 0.0, 0.0, 1.0, 1.0  }, // Bottom left
};

// Create variables for storing the ID of our VAO and VBO
GLuint vbo[2], vao[1]; 

// The positons of the position and color data within the VAO
const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;

Shader shader;

/*std::string LoadShaderFile(std::string strFile) {
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
}*/

void init();
bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);


bool SetOpenGlAttributes() {
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

void init() {
	SDL_Init(SDL_INIT_VIDEO);

	// Will use OpenGL 4.4

	// Creating window
	window = SDL_CreateWindow("4D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

	SetOpenGlAttributes();

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
}
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


void SetupBufferObjects()
{
	// Generate and assign two Vertex Buffer Objects to our handle
	glGenBuffers(2, vbo);

	// Generate and assign a Vertex Array Object to our handle
	glGenVertexArrays(1, vao);

	// Bind our Vertex Array Object as the current used object
	glBindVertexArray(vao[0]);

	// Positions
	// ===================
	// Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// Copy the vertex data from diamond to our buffer
	glBufferData(GL_ARRAY_BUFFER, ( points * floatsPerPoint) * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable our attribute within the current VAO
	glEnableVertexAttribArray(positionAttributeIndex);

	// Colors
	// =======================
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	// Copy the vertex data from diamond to our buffer
	glBufferData(GL_ARRAY_BUFFER, ( points * floatsPerColor) * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
	glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// Note : We didn't enable the colors here!

	// Set up shader ( will be covered in the next part )
	// ===================
	shader.Init();

	shader.BindAttributeLocation(0, "in_Position");
	shader.BindAttributeLocation(1, "in_Colors");
	shader.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Render()
{
	// First, render a square without any colors ( all vertexes will be black )
	// ===================
	// Make our background grey
	/*glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	// Swap our buffers to make our changes visible
	SDL_GL_SwapWindow(window);

	std::cout << "Press ENTER to render next frame\n";
	std::cin.ignore();*/

	// Second, enable the colors and draw a solid square
	// ===================
	// Enable our attribute within the current VAO
	glEnableVertexAttribArray(colorAttributeIndex);

	// Make our background black*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// Swap our buffers to make our changes visible
	SDL_GL_SwapWindow(window);

}

void close() {
	shader.CleanUp();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

int main(int argc, char const *argv[]) {
	// First, we initiallize our stuff.
	 init(/*"../shaders/shader.vertex", "../shaders/shader.fragment"*/);
	SetupBufferObjects();


	// Creating event. It's what will hold the window.
	SDL_Event windowEvent;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)) break;
		}
    	// now you can make GL calls.
    	// Display();
    	// glUseProgram(shaderProgram);
		Render();


		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		// glUseProgram(NULL);
    	// SwapWindow will pass GL context to window.
		SDL_GL_SwapWindow(window);
	}

	// Break has been called, let's close everything.
	close();
	return 0;
}

void CheckSDLError(int line = -1)
{
	std::string error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

void PrintSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
