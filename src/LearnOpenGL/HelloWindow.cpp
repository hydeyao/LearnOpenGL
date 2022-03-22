#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_cb(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void clearBuffer() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
	//init GLFW
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//new window obj
	GLFWwindow* window = glfwCreateWindow(800, 600, "demo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to Creat Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//resize frame size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);
	//load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to load GLAD" << std::endl;
		return -1;
	}

	//äÖÈ¾Ñ­»·
	while (!glfwWindowShouldClose(window))
	{
		//wait key input esc
		processInput(window);

		//close
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_cb(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		clearBuffer();
	}
}
