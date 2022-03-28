#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include "Shader.h"
#include <list>

#define VERTEX_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\shader.vs"
#define FRAGMENT_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\shader.fs"
#define TEXTURE_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\container.jpg"
#define TEXTURE_FACE_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\face.png"


class Texture
{
public:
	Texture(const char* texturePath, int fliptype = 0);
	~Texture();
	int bindTexture();
	unsigned int TEXTURE_ID;
private:
	int m_nwidth, m_nheight, m_nrchannels;
	unsigned char* mucTextualData;
	int m_flipType;
	int m_texFormat;

	enum TEXTURE_FORMAT
	{
		TP_RGB = 0,
		TP_RGBA = 1
	};

private:
	int loadTextual(const char* texturePath);
	int initTextrue();

	__inline int getTexFormat(std::string texPath) { return ("png" == texPath.substr(texPath.length() - 3, 3)) ? TP_RGBA : TP_RGB; }
};

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
	std::shared_ptr<Texture> msp_texture;

public:
	int showWindow();
private:
	int setVertexAtrrib(unsigned int& VAO,unsigned int& VBO,unsigned int& EBO);
	int render(GLFWwindow* window,Shader* shader,unsigned int VAO,Texture* texture);
	int render(GLFWwindow* window,Shader* shader,unsigned int VAO, unsigned int texarr[2]);

	__inline void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};



