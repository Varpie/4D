// No copyrights, it's free.

#pragma once

class Model {
	public:

	Shader shader;

	std::vector<GLfloat> positions;
	// std::vector<GLfloat> colors;

	// Our object has 8 /*points*/8
	// const uint32_t /*points*/8 = 8;

	// Each poin has three values ( x, y, z)
	// const uint32_t /*floatsPerPoint*/3 = 3;

	// Each color has 4 values ( red, green, blue, alpha )
	// const uint32_t /*floatsPerColor*/4 = 4;

	// This is the object we'll draw ( a simple square
	const GLfloat diamond[/*points*/8][/*floatsPerPoint*/3] = {
		// I want a square, so I have to set the width at height/screen ratio.
		{ -0.5*SCREEN_HEIGHT/SCREEN_WIDTH,  0.5,  0.5 }, // Top left
		{  0.5*SCREEN_HEIGHT/SCREEN_WIDTH,  0.5,  0.5 }, // Top right
		{  0.5*SCREEN_HEIGHT/SCREEN_WIDTH, -0.5,  0.5 }, // Bottom right 
		{ -0.5*SCREEN_HEIGHT/SCREEN_WIDTH, -0.5,  0.5 }, // Bottom left
		{ -0.5*SCREEN_HEIGHT/SCREEN_WIDTH,  0.5, -0.5 }, // Top left
		{  0.5*SCREEN_HEIGHT/SCREEN_WIDTH,  0.5, -0.5 }, // Top right
		{  0.5*SCREEN_HEIGHT/SCREEN_WIDTH, -0.5, -0.5 }, // Bottom right 
		{ -0.5*SCREEN_HEIGHT/SCREEN_WIDTH, -0.5, -0.5 }, // Bottom left
	};

	// This is the object we'll draw ( a simple square
	const GLfloat colors[/*points*/8][/*floatsPerColor*/4] = {
		{ 0.0, 1.0, 0.0, 1.0 }, // Top left
		{ 1.0, 1.0, 0.0, 1.0 }, // Top right
		{ 1.0, 0.0, 0.0, 1.0 }, // Bottom right 
		{ 0.0, 0.0, 1.0, 1.0 }, // Bottom left
		{ 0.0, 1.0, 0.0, 1.0 }, // Top left
		{ 1.0, 1.0, 0.0, 1.0 }, // Top right
		{ 1.0, 0.0, 0.0, 1.0 }, // Bottom right 
		{ 0.0, 0.0, 1.0, 1.0 }, // Bottom left
	};

	GLuint vbo[2], vao[1];
	const uint32_t positionAttributeIndex, colorAttributeIndex;

	Model()
		:	positionAttributeIndex(0)
		,	colorAttributeIndex(1) {
	}

	bool setupBufferObjects() {
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
		glBufferData(GL_ARRAY_BUFFER, ( /*points*/8 * /*floatsPerPoint*/3) * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

		// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
		glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Colors
		// =======================
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		// Copy the vertex data from colors to our buffer
		glBufferData(GL_ARRAY_BUFFER, ( /*points*/8 * /*floatsPerColor*/4) * sizeof(GLfloat), colors, GL_STATIC_DRAW);

		// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
		glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(positionAttributeIndex);
		glEnableVertexAttribArray(colorAttributeIndex);

		// Set up shader ( will be covered in the next part )
		// ===================
		shader.init();

		shader.bindAttributeLocation(0, "in_Position");
		shader.bindAttributeLocation(1, "in_Colors");
		shader.useProgram();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return true;
	}
};