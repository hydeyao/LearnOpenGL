#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include "Shader.h"

#define VERTEX_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\shader.vs"
#define FRAGMENT_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\shader.fs"


class TextureShow
{
public:
	TextureShow();
	~TextureShow();
public:
	GLFWwindow* m_window;
	unsigned int m_VAO, m_VBO, m_EBO, m_Texture;
	static const int m_width = 800;
	static const int m_height = 600;
	std::shared_ptr<Shader> msp_shader;

public:
	int showWindow();
private:
	int setVertexAtrrib(unsigned int VAO,unsigned int VBO,unsigned int EBO, float* vertices, float* indices);
	int render(GLFWwindow* window,Shader shader,unsigned int VAO,unsigned int texture);
	//int setTextureAtrrib();

	__inline void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};

class Texture
{
public:
	Texture(const char * texturePath);
	~Texture();

private:
};

