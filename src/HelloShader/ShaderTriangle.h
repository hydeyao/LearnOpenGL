#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class ShaderTriangle
{
public:
	ShaderTriangle();
	~ShaderTriangle() {};

public:
	int initShader(unsigned int& shaderPro);
	int showTriangle();
	int renderLoop(GLFWwindow* window, unsigned int shaderProg, unsigned int VAO, unsigned int VBO, int drawType = 0);
	void pressInput(GLFWwindow* window);
};

