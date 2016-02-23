// I've found this file on headerfile.com, adapted it to fit my coding style.

#pragma once
 
class Shader {
	public:

	// The handle to our shader program
	GLuint shaderProgram;
 
	// The handles to the induvidual shader
	GLuint vertexshader, fragmentShader;
 
	// The source code of the shaders
	GLchar *vertexsource, *fragmentSource;
 
	int isCompiled_VS, isCompiled_FS;
 
	int maxLength;
	char *shaderInfoLog;
	char *shaderProgramInfoLog;
 
	int isLinked;

	// Shader() {
		
	// }

	std::string readFile(const char* file) {
		// Open file
		std::ifstream t(file);
 
		// Read file into buffer
		std::stringstream buffer;
		buffer << t.rdbuf();
 
		// Make a std::string and fill it with the contents of buffer
		std::string fileContent = buffer.str();
		fileContent += '\0';
 
		return fileContent;
	}
 
	void bindAttributeLocation(int index, const std::string &attribute) {
		// Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color
		// Attribute locations must be setup before calling glLinkProgram
		glBindAttribLocation(shaderProgram, index, attribute.c_str());
	}
 
	void init() {
		vertexshader = loadShader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
		fragmentShader = loadShader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);
 
		/* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
		/* We must link them together to make a GL shader program */
		/* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
		/* Assign our program handle a "name" */
		shaderProgram = glCreateProgram();
 
		/* Attach our shaders to our program */
		glAttachShader(shaderProgram, vertexshader);
		glAttachShader(shaderProgram, fragmentShader);
 
		linkShaders();
	}
 
	void useProgram() {
		/* Load the shader into the rendering pipeline */
		glUseProgram(shaderProgram);
	}
 
	GLuint loadShader(const std::string &filename, GLenum shaderType) {
		std::cout << "Loading shader : " << filename << std::endl;
		// Read file as 
		std::string str = readFile(filename.c_str());
 
		// c_str() gives us a const char*, but we need a non-const one
		char* src = const_cast<char*>( str.c_str());
		
		/* Create an empty vertex shader handle */
		GLuint shader = glCreateShader(shaderType);
 
		/* Send the vertex shader source code to GL */
		/* Note that the source code is NULL character terminated. */
		/* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
		glShaderSource(shader, 1, &src, 0);
 
		/* Compile the vertex shader */
		glCompileShader(shader);
 
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled_VS);
 
		if (isCompiled_VS == false) {
			std::cout << "Shader compilation failed : " << shader << std::endl;
 
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
 
			/* The maxLength includes the NULL character */
			shaderInfoLog = (char *)malloc(maxLength);
 
			glGetShaderInfoLog(shader, maxLength, &maxLength, shaderInfoLog);
 
			std::cout << "info : " << shaderInfoLog << std::endl;
 
			/* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
			/* In this simple program, we'll just leave */
			free(shaderInfoLog);
			return NULL;
		}

		return shader;
 
	}

	void linkShaders() {
		/* Link our program */
		/* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
		/* The binary code is uploaded to the GPU, if there is no error. */
		glLinkProgram(shaderProgram);
 
		/* Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex */
		/* and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or */
		/* too many texel fetch instructions or too many interpolators or dynamic loops. */
 
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == false) {
			std::cout << "Not linked : shaderProgram" << std::endl;
 
			/* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
 
			/* The maxLength includes the NULL character */
			shaderProgramInfoLog = (char *)malloc(maxLength);
 
			/* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
			glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

			std::cout << "MSG : " << shaderProgramInfoLog << std::endl;
 
			/* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
			/* In this simple program, we'll just leave */
			free(shaderProgramInfoLog);
			return;
		}
	}
 
	void cleanUp() {
		/* Cleanup all the things we bound and allocated */
		glUseProgram(0);
		glDetachShader(shaderProgram, vertexshader);
		glDetachShader(shaderProgram, fragmentShader);

		glDeleteProgram(shaderProgram);

		glDeleteShader(vertexshader);
		glDeleteShader(fragmentShader);

		free(vertexsource);
	}
 
};
