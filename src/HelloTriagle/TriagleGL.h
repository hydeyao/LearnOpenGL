#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class TriagleGL
{
public:
	TriagleGL();
	~TriagleGL() {};

public:
	int triagleDemo();
	int initGLFWWithShader(unsigned int &shaderProg);
	void pressInput(GLFWwindow* window);
	virtual int renderLoop(GLFWwindow* window, unsigned int shaderProg,unsigned int VAO, unsigned int VBO,int drawType = 0 );
};

class TraigleIndex : public TriagleGL
{
public:
	TraigleIndex();
	~TraigleIndex() {};

public:
	int showTriagleIndex();
	virtual int renderLoop(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO, unsigned int VBO,int drawType = 0) override;
	int triagleExe_1();
	int triagleExe_2();

private:
	int exc2Render(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO[2], unsigned int VBO[2], int drawType);
	int exc2Render(GLFWwindow* window, unsigned int shaderProg, unsigned int secShaderPro,unsigned int VAO[2], unsigned int VBO[2], int drawType);

	int initShader(unsigned int &shaderPro);
};

