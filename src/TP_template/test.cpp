#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <string>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Texture.hpp>
#include <glimac/MatrixManager.hpp>
#include <glimac/MapGenerator.hpp>
#include <glimac/PPMParser.hpp>
#include <glimac/DataParser.hpp>
#include <glimac/SixAdjacencyCamera.hpp>

using namespace glimac;

struct Vertex3DText
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 textureCoord;

    Vertex3DText() {}
    Vertex3DText(glm::vec3 pos, glm::vec3 nor, glm::vec3 tex) : position{pos}, normal{nor}, textureCoord{tex} {}
};

int main(int argc, char **argv)
{

    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "GLImac");

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // GENERATION DE LA MAP
    std::string dataFile = argv[1];
    DataParser data{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/data/" + dataFile};
    PPMParser mapParsed("/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/map/room.ppm");
    MapGenerator map(&mapParsed);

    // GESTION DES SHADERS

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/3DAlpha.vs.glsl",
        applicationPath.dirPath() + "shaders/text3DAlpha.fs.glsl");

    program.use();

    // RECUPERATION DES LOCATION DES VARIABLES UNIFORMES

    GLint uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

    // CREATION DES MATRIX

    glm::mat4 globalProjectionMatrix = glm::perspective(glm::radians(70.f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, .1f, 100.f);
    glm::mat4 globalMVMatrix = glm::mat4(1.f);

    auto playerDirection = map.getFirstDirection();
    auto angle = 90.f * playerDirection.x + 180.f * (playerDirection.y > 0);

    globalMVMatrix = glm::rotate(globalMVMatrix, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));

    // CREATION DE LA CAMERA

    SixAdjacencyCamera camera{playerDirection, &globalMVMatrix, &map};

    // CREATION DES BUFFERS

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE_COORDINATE = 2;

    GLuint vbo;
    GLuint vao;

    auto quadNormal = glm::cross(glm::vec3(-.5f, -.5f, 0.f), glm::vec3(.5f, .5f, 0.f));

    Vertex3DText vertices[] = {
        Vertex3DText(glm::vec3(-.5f, -.5f, 0.f), quadNormal, glm::vec3(0.f, 1.f, 0.f)),
        Vertex3DText(glm::vec3(.5f, -.5f, 0.f), quadNormal, glm::vec3(1.f, 1.f, 0.f)),
        Vertex3DText(glm::vec3(.5f, .5f, 0.f), quadNormal, glm::vec3(1.f, 0.f, 0.f)),
        Vertex3DText(glm::vec3(-.5f, -.5f, 0.f), quadNormal, glm::vec3(0.f, 1.f, 0.f)),
        Vertex3DText(glm::vec3(.5f, .5f, 0.f), quadNormal, glm::vec3(1.f, 0.f, 0.f)),
        Vertex3DText(glm::vec3(-.5f, .5f, 0.f), quadNormal, glm::vec3(0.f, 0.f, 0.f)),
    };

    // BIND DU VBO

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DText), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // BIND DU VAO

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DText), offsetof(Vertex3DText, position));

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DText), (const GLvoid *)offsetof(Vertex3DText, normal));

    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE_COORDINATE);
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DText), (const GLvoid *)offsetof(Vertex3DText, textureCoord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // BOUCLE D'APPLICATION

    bool done = false;
    while (!done)
    {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                done = true; // Leave the loop after this iteration
            }
            if (e.type == SDL_KEYDOWN)
            {
                glm::vec2 target;
                switch (e.key.keysym.sym)
                {
                case SDLK_z:
                    camera.moveFront();
                    break;
                case SDLK_s:
                    camera.moveBack();
                    break;
                case SDLK_q:
                    camera.moveLeft();
                    break;
                case SDLK_d:
                    camera.moveRight();
                    break;
                case SDLK_a:
                    camera.rotateLeft();
                    break;
                case SDLK_e:
                    camera.rotateRight();
                    break;
                }
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        map.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, &globalProjectionMatrix, globalMVMatrix);
        glBindVertexArray(0);
        // Update the display
        windowManager.swapBuffers();
    }

    // NETTOYAGE

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    map.deleteMap();

    return EXIT_SUCCESS;
}
