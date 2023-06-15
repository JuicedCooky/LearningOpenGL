#include <glad/glad.h> 
#include <GLFW/glfw3.h>
void framebuffer_size_callback(GLFWwindow*, int width, int height) 
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{ //glfwGetKey (the window, the key pressed)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //GLFW_RELEASE VS GLFW_PRESS
		glfwSetWindowShouldClose(window, true); //close flag set true
}