#include "Texture.h"

Texture::Texture(const char* texturePath, int fliptype) :m_nwidth(0), m_nheight(0), m_nrchannels(0), mucTextualData(NULL), TEXTURE_ID(0), m_flipType(fliptype)
{
    m_texFormat = getTexFormat(texturePath);
    initTextrue();
    loadTextual(texturePath);
}

Texture::~Texture()
{
    stbi_image_free(mucTextualData);
}

int Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID);
    return 0;
}

int Texture::loadTextual(const char* texturePath)
{
    mucTextualData = stbi_load(texturePath, &m_nwidth, &m_nheight, &m_nrchannels, 0);
    if (mucTextualData)
    {

        if (m_texFormat == TEXTURE_FORMAT::TP_RGBA)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nwidth, m_nheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mucTextualData);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nwidth, m_nheight, 0, GL_RGB, GL_UNSIGNED_BYTE, mucTextualData);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    return 0;
}


int Texture::initTextrue()
{
    unsigned int id_tex;
    glGenTextures(1, &id_tex);
    glBindTexture(GL_TEXTURE_2D, id_tex); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_flipType)
    {
        stbi_set_flip_vertically_on_load(true);
    }
    // load image, create texture and generate mipmaps
    TEXTURE_ID = id_tex;
    return 0;
}