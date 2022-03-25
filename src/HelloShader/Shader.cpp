#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fregmentPath):ID(0)
{
	std::string strVertexCode, strFragmentCode;
	readShaderFromFile(vertexPath, fregmentPath, strVertexCode, strFragmentCode);
	buildShaderProgram(strVertexCode, strFragmentCode, ID);

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
		fShaderFile.open(fregmentPath);
		std::stringstream ssVertex, ssFregment;
		ssVertex << vShaderFile.rdbuf();
		ssFregment << fShaderFile.rdbuf();

		vertexCode = ssVertex.str();
		fregmentCode = ssFregment.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << e.what() << std::endl;
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
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, uiVertex);
	glAttachShader(shaderProgram, uiFragmet);
	glLinkProgram(shaderProgram);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, clog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << clog << std::endl;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(uiVertex);
	glDeleteShader(uiFragmet);
	return 0;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setParam(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setParam(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setParam(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

