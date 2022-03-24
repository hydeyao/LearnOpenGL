#include "TriagleGL.h"


void framebuffer_size_cb(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

TriagleGL::TriagleGL()
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int TriagleGL::triagleDemo()
{
	GLFWwindow*  window = glfwCreateWindow(800, 600, "demo", NULL, NULL);
	//new window obj
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

	unsigned int shaderProgram;
	initGLFWWithShader(shaderProgram);

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
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	renderLoop(window,shaderProgram,VAO,VBO);

	return 0;
}

int TriagleGL::initGLFWWithShader(unsigned int &shaderProg)
{
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


	//init GLFW	//构建编译着色器程序
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
	glCompileShader(fragmentShader);

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

	shaderProg = shaderProgram;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return 0;
}



void TriagleGL::pressInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int TriagleGL::renderLoop(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO,unsigned int VBO,int drawType)
{
	//渲染
	while (!glfwWindowShouldClose(window))
	{
		pressInput(window);

		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw 
		glUseProgram(shaderProg);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProg);

	glfwTerminate();
	return 0;
}

TraigleIndex::TraigleIndex():TriagleGL()
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int TraigleIndex::showTriagleIndex()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "demo", NULL, NULL);
	//new window obj
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

	unsigned int shaderProgram;
	initGLFWWithShader(shaderProgram);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	renderLoop(window, shaderProgram, VAO, VBO);
	glDeleteBuffers(1,&EBO);
	return 0;
}

int TraigleIndex::renderLoop(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO, unsigned int VBO,int drawType)
{
	//渲染
	while (!glfwWindowShouldClose(window))
	{
		pressInput(window);

		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw 
		glUseProgram(shaderProg);
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (drawType == 1)
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProg);

	glfwTerminate();
	return 0;

}

int TraigleIndex::triagleExe_1()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "demo", NULL, NULL);
	//new window obj
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

	unsigned int shaderProgram;
	initGLFWWithShader(shaderProgram);

	float vertices[] = {
		//first 
		-0.5f,0.5f,0.0f,
		-1.0f,0.0f,0.0f,
		-0.5f,0.0f,0.0f,
		//sec
		-0.4f,0.5f,0.0f,
		-0.4f,0.0f,0.0f,
		 0.1f,0.0f,0.0f
	};


	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	renderLoop(window, shaderProgram, VAO, VBO,1);

	return 0;
}

int TraigleIndex::triagleExe_2()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "demo", NULL, NULL);
	//new window obj
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

	unsigned int shaderProgram ,secShaderPro;
	initGLFWWithShader(shaderProgram);
	initShader(secShaderPro);
	float firstVer[] = {
		-0.5f,0.5f,0.0f,
		-1.0f,0.0f,0.0f,
		-0.5f,0.0f,0.0f
	};

	float SecondVer[] = {
	-0.4f,0.5f,0.0f,
	-0.4f,0.0f,0.0f,
	 0.1f,0.0f,0.0f
	};

	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstVer), firstVer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//sec
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SecondVer), SecondVer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FLOAT, 0, (void*)0);
	glEnableVertexAttribArray(0);

	exc2Render(window, shaderProgram,secShaderPro, VAOs, VBOs,0);

	return 0;

	
}

int TraigleIndex::exc2Render(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO[2], unsigned int VBO[2], int drawType)
{
	//渲染
	while (!glfwWindowShouldClose(window))
	{
		pressInput(window);

		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw 
		glUseProgram(shaderProg);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(1, VBO);
	glDeleteProgram(shaderProg);

	glfwTerminate();
	return 0;

}

int TraigleIndex::exc2Render(GLFWwindow* window, unsigned int shaderProg, unsigned int secShaderPro, unsigned int VAO[2], unsigned int VBO[2], int drawType)
{
	//渲染
	while (!glfwWindowShouldClose(window))
	{
		pressInput(window);

		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw 
		glUseProgram(shaderProg);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(secShaderPro);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(secShaderPro, "ourColor");
		glUseProgram(secShaderPro);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(1, VBO);
	glDeleteProgram(shaderProg);
	glDeleteProgram(secShaderPro);
	glfwTerminate();
	return 0;
}

int TraigleIndex::initShader(unsigned int& shaderPro)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";


	//init GLFW	//构建编译着色器程序
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
	glCompileShader(fragmentShader);

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

	shaderPro = shaderProgram;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return 0;
}
