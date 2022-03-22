#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_cb(GLFWwindow * window, int width, int height);

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

	//构建编译着色器程序
	//顶点着色器
	 unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

}

void framebuffer_size_cb(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void pressInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

}
