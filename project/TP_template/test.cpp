#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

struct Vertex2DColor
{
    glm::vec2 position;
    glm::vec2 textureCoord;

    Vertex2DColor() {}
    Vertex2DColor(glm::vec2 pos, glm::vec2 tex) : position{pos}, textureCoord{tex} {}
};

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    std::unique_ptr<Image> texturePtr;

    if ((texturePtr = loadImage(FilePath("/home/thomas2dumont/Computer_Graphics/GLImac-Template/assets/textures/triforce.png"))) == NULL)
    {
        std::cerr << "TEXTURE NOT LOADED" << std::endl;
        return EXIT_FAILURE;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texturePtr->getWidth(), texturePtr->getHeight(), 0, GL_RGBA, GL_FLOAT, texturePtr->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/text2D.vs.glsl",
        applicationPath.dirPath() + "shaders/text2D.fs.glsl");

    program.use();

    GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

    const GLuint VERTEX_ATTR_POSITION = 3;
    const GLuint VERTEX_ATTR_TEXTURE_COORDINATE = 8;

    GLuint vbo;
    GLuint vao;
    Vertex2DColor vertices[] = {
        Vertex2DColor(glm::vec2(-.5f, -.5f), glm::vec2(0.f, 1.f)),
        Vertex2DColor(glm::vec2(.5f, -.5f), glm::vec2(1.f, 1.f)),
        Vertex2DColor(glm::vec2(.5f, .5f), glm::vec2(1.f, 0.f)),
        Vertex2DColor(glm::vec2(-.5f, -.5f), glm::vec2(0.f, 1.f)),
        Vertex2DColor(glm::vec2(.5f, .5f), glm::vec2(1.f, 0.f)),
        Vertex2DColor(glm::vec2(-.5f, .5f), glm::vec2(0.f, 0.f)),
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), offsetof(Vertex2DColor, position));

    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE_COORDINATE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE_COORDINATE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid *)offsetof(Vertex2DColor, textureCoord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while (!done)
    {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(uTextureLocation, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &texture);

    return EXIT_SUCCESS;
}
