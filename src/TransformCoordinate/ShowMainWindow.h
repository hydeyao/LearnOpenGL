#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Shader.h"
#include "Texture.h"
#include <list>
#include <vector>

#define VERTEX_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\corShader.vs"
#define FRAGMENT_SHADER_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\corShader.fs"
#define TEXTURE_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\container.jpg"
#define TEXTURE_FACE_RESOURSE_PATH  "D:\\GitRep\\LearnOpenGL\\resourses\\face.png"


class ShowMainWindow
{
public:
	ShowMainWindow();
	~ShowMainWindow();
private :
	GLFWwindow* m_window;
	unsigned int m_VAO, m_VBO, m_EBO, m_Texture;
	static const int m_width = 800;
	static const int m_height = 600;
	std::shared_ptr<Shader> msp_shader;
	std::shared_ptr<Texture> msp_texture;
	std::vector<glm::vec3> msp_veCudePos;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void zoom_callback(GLFWwindow* window, double xoff ,double yoff);

public:
	int showWindow();
private:
	int setVertexAtrrib(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	int setCorVertexAtrrib(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

	int render(GLFWwindow* window, Shader* shader, unsigned int VAO, Texture* texture);
	int render(GLFWwindow* window, Shader* shader, unsigned int VAO, unsigned int texarr[2]);
	int corriRender(GLFWwindow* window, Shader* shader, unsigned int VAO, unsigned int texarr[2]);
	int camRender(GLFWwindow* window, Shader* shader, unsigned int VAO, unsigned int texarr[2]);

	void processInput(GLFWwindow* window);


};

