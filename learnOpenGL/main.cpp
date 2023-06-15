#include <glad/glad.h> // has required openGL headers, add before other headers that require openGL
#include <GLFW/glfw3.h>
#include <iostream>
#include <window_functions.h>

//modern OpenGL we are required to define at least a vertex and fragment shader of out own, no defaults



//1.


int main() {


	//SETUP_______________________________________________________________________________________________________________________________________________________________
	glfwInit(); //initialize GLFW
	//first argument = option, GLFW_ ...
	//second = integer that sets value, see documentation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //use core profile, from glad api website, smaller subset of openGL without backwards-compatible features
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//(width,height,name,,) ; returns a GLFWwindow object
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//loads function depending on hardware
						//load address of openGL function pointers , glfwGetProcAddress defines correct function based on OS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//tell open GL the size of window
	//(location of lower x, location of lower x, width, height), can set dimension smaller than glfw
	glViewport(0, 0, 800, 600);
	
	//When resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//_______________________________________________________________________________________________________________________________________________________________________________
	


	//  -1 to 1 (normalized device coordinates; visible on screen); x,y,z
	float vertices[] = {
		-0.5,-0.5,0.0,
		 0.5,-0.5,0.0,
		 0.0, 0.5,0.0
	};
	//1. vertex shader*
	//	create memory to send to gpu of vertex data, how to interpret, send data for vertex shader
	//	VBO (vertex buffer objects) = store large number of vertices in gpu memory, large batches of data at once, send as much as possible to gpu
	unsigned int VBO; 
	glGenBuffers(1, &VBO); //OpenGl object glGenBuffers is a unique ID
	//GL_ARRAY_BUFFER is a vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binding created buffer to the vertex buffer object (can bind to multiple if they are all different)
	//now GL_ARRAY_BUFFER has VBO bound, and any calls on the GL_ARRAY_BUFFER configures VBO
	//(type of data to copy into, size of data, data to send, how to manage the data*)
	//*
	//GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	//GL_STATIC_DRAW : the data is set only once and used many times. //static but on screen a lot
	//GL_DYNAMIC_DRAW : the data is changed a lot and used many times //faster writes
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copy user data to buffer

	//2. shape assembly
	// 
	//3. geometry shader*
	//4. tests and blending
	//5. fragment shader*
	//6. rasterization


	

	//a "render loop", while loop to keep GLFW to keep rendering until stopped
	while (!glfwWindowShouldClose(window)) //glfwWindowShouldClose checks at the start of each loop if GLFW has been instructed to stop, returns true if told to stop
	{ 
		//input 
		processInput(window);
		//rendering commands, want to execute rendering at each frame
		glClearColor(0.2f, 0.3f, 0.3, 1.0f); //color to clear the screen //state setting function
		glClear(GL_COLOR_BUFFER_BIT);//clear buffer //state-using function
		//checking and calling events 
		glfwSwapBuffers(window); //swap color buffer, 
		glfwPollEvents();//checks if any events triggered, calls corrosponding functions
	}


	//double buffer, two buffers, one for final output, another "back" buffer that gets updated completely
	glfwTerminate(); //terminate instiated objects

	return 0;
}