#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fregmentPath)
{
	ID = 0;
}

int Shader::readShaderFromFile(const char* vertexPath, const char* fregmentPath, std::string& vertexCode, std::string& fregmentCode)
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		vShaderFile.open(fregmentPath);
		std::stringstream ssVertex, ssFregment;
		ssVertex << vShaderFile.rdbuf();
		ssFregment << fShaderFile.rdbuf();

		vertexCode = ssVertex.str();
		fregmentCode = ssFregment.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return 0;
}

int Shader::buildShaderProgram(std::string vertexCode, std::string frementCode, unsigned int& shaderProgram)
{
	const char* vertexSrc = vertexCode.c_str();
	const char* fregmentSrc = frementCode.c_str();
	unsigned int uiVertex, uiFragmet;
	int success;
	char clog[512];

	//vertex shader
	uiVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(uiVertex, 1, &vertexSrc, NULL);
	glCompileShader(uiVertex);

	glGetShaderiv(uiVertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(uiVertex, 512, NULL, clog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << clog << std::endl;
	}

	//fragment shader
	uiFragmet = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(uiFragmet, 1, &fregmentSrc, NULL);
	glCompileShader(uiFragmet);

	glGetShaderiv(uiFragmet, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(uiFragmet, 512, NULL, clog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << clog << std::endl;
	}

	//link 

	return 0;
}

