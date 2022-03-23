#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_cb(GLFWwindow * window, int width, int height);
void pressInput(GLFWwindow* window);

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
	 glCompileShader(vertexShader);

	 int successFlag = 0;
	 char infoLog[512];
	 glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successFlag);
	 if (!successFlag)
	 {
		 glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		 std::cout << "ERROR::SHADER::VERTEX::COMPLILATION::FAILED\n" << infoLog << std::endl;
	 }

	 //片段着色器
	 unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	 glCompileShader(vertexShader);

	 glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFlag);
	 if (!successFlag)
	 {
		 glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		 std::cout << "ERROR::SHADER::FRAGMENT::COMPLILATION::FAILED\n" << infoLog << std::endl;
	 }

	 //链接着色器
	 unsigned int shaderProgram = glCreateProgram();
	 glAttachShader(shaderProgram, vertexShader);
	 glAttachShader(shaderProgram, fragmentShader);
	 glLinkProgram(shaderProgram);

	 //check Link Error
	 glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successFlag);
	 if (!successFlag)
	 {
		 glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		 std::cout << "ERROR::SHADER::PROGRAM::LINK::FAILED\n" << infoLog << std::endl;
	 }

	 //设置顶点坐标
	 float vertices[] = {
		 -0.5f, -0.5f, 0,
		 0.5f, -0.5f, 0,
		 -0.0f, 0.5f, 0
	 };
	 
	 unsigned int VBO, VAO;
	 glGenVertexArrays(1, &VAO);
	 glGenBuffers(1, &VBO);

	 //绑定VAO
	 glBindVertexArray(VAO);
	 //复制顶点数组到buff
	 glBindBuffer(GL_ARRAY_BUFFER,VBO);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	 //设置顶点属性指针
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);

	 //渲染
	 while (!glfwWindowShouldClose(window))
	 {
		 pressInput(window);

		 //渲染
		 glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		 glClear(GL_COLOR_BUFFER_BIT);

		 //draw 
		 glUseProgram(shaderProgram);
		 glBindVertexArray(VAO);
		 glDrawArrays(GL_TRIANGLES, 0, 3);

		 glfwSwapBuffers(window);
		 glfwPollEvents();
	 }

	 glDeleteVertexArrays(1, &VAO);
	 glDeleteBuffers(1, &VBO);
	 glDeleteProgram(shaderProgram);

	 glfwTerminate();
	 return 0;
}

void framebuffer_size_cb(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void pressInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

}
