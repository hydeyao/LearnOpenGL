#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include "Shader.h"
#include <list>
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
	
	enum class TEXTURE_FORMAT
	{
		TP_RGB = 0,
		TP_RGBA = 1
	};

	TEXTURE_FORMAT m_texFormat;


private:
	int loadTextual(const char* texturePath);
	int initTextrue();

	__inline TEXTURE_FORMAT getTexFormat(std::string texPath) { return ("png" == texPath.substr(texPath.length() - 3, 3)) ? \
		TEXTURE_FORMAT::TP_RGBA : TEXTURE_FORMAT::TP_RGB; }
};

