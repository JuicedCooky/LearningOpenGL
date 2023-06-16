#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int x, int y) {
	glViewport(0, 0, x, y);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "RECTANGLE", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader[2];
	unsigned int shaderProgram[2];
	for (int i = 0; i < 2; i++)
	{
		fragmentShader[i] = glCreateShader(GL_FRAGMENT_SHADER);
		shaderProgram[i] = glCreateProgram();
	};
	 
	const char* fragmentShaderSourceArray[] = { fragmentShaderSource, fragmentShaderSource2 };
	for (int i = 0; i < 2; i++)
	{
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		
		glShaderSource(fragmentShader[i], 1, &(fragmentShaderSourceArray[i]), NULL);
		glCompileShader(fragmentShader[i]);

		
		glAttachShader(shaderProgram[i], vertexShader);
		glAttachShader(shaderProgram[i], fragmentShader[i]);
		glLinkProgram(shaderProgram[i]);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader[i]);

	}


	unsigned int VBO[2], VAO[2];
	float verticies3[2][9] = {
		{//triangle 1
		-0.5f,  0.5f, 0.0f,  // top middle
		 0.0f, -0.5f, 0.0f,  // bottom right
		-1.0f, -0.5f, 0.0f,  // bottom left
		},
		{//triangle 2
		 0.5f,  0.5f, 0.0f,  // top middle
		 1.0f, -0.5f, 0.0f,  // bottom right
		 0.0f, -0.5f, 0.0f,  // bottom left
		}
	};
	for (int i = 0; i < 2; i++)
	{
		glGenVertexArrays(1, &VAO[i]);
		glGenBuffers(1, &VBO[i]);

		glBindVertexArray(VAO[i]); //bind vertex array objcet first

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies3[i]), verticies3[i], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram[0]);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram[1]);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteProgram(shaderProgram[0]);
	glDeleteProgram(shaderProgram[1]);

	glfwTerminate();
	return 0;
}