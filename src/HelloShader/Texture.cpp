#include "Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {   glViewport(0, 0, width, height); }

TextureShow::TextureShow() :m_VAO(0), m_VBO(0), m_EBO(0), m_Texture(0)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_width, m_height, "Texture", NULL, NULL);

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    msp_shader.reset(new Shader(VERTEX_SHADER_RESOURSE_PATH, FRAGMENT_SHADER_RESOURSE_PATH));
    msp_texture.reset(new Texture(TEXTURE_RESOURSE_PATH));

}

TextureShow::~TextureShow()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

}

int TextureShow::showWindow()
{
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    setVertexAtrrib(m_VAO, m_VBO, m_EBO);

    Texture *Tex_box = new Texture(TEXTURE_RESOURSE_PATH,1);
    Texture *Tex_face = new Texture(TEXTURE_FACE_RESOURSE_PATH,2);

    unsigned int texarr[] = {
        Tex_box->TEXTURE_ID,
        Tex_face->TEXTURE_ID
    };
    msp_shader->use();
    glUniform1i(glGetUniformLocation(msp_shader->ID, "texture1"), 0);
    msp_shader->setParam("texture2", 1);
    render(m_window, msp_shader.get(), m_VAO, texarr);

    glfwTerminate();
    return 0;
}

int TextureShow::setVertexAtrrib(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    return 0;
}

int TextureShow::render(GLFWwindow* window, Shader* shader, unsigned int VAO, Texture* texture)
{
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture->TEXTURE_ID);

        // render container
        shader->use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

int TextureShow::render(GLFWwindow* window, Shader* shader, unsigned int VAO, unsigned int texarr[2])
{
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        //glBindTexture(GL_TEXTURE_2D, texture->TEXTURE_ID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texarr[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texarr[1]);

        shader->use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

Texture::Texture(const char* texturePath,int fliptype):m_nwidth(0), m_nheight(0), m_nrchannels(0), mucTextualData(NULL), TEXTURE_ID(0), m_flipType(fliptype)
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