#pragma once

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define IN
#define OUT

class Shader
{
public:
	Shader(const char* vertexPath, const char* fregmentPath);
	~Shader() {};
public:
	unsigned int ID;

private:
	int readShaderFromFile(const char* vertexPath,const char* fregmentPath,std::string &vertexCode,std::string &fregmentCode);
	int buildShaderProgram(std::string vertexCode, std::string frementCode,unsigned int & shaderProgram);
public:
	void use();
	// uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	
};

