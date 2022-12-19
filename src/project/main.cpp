/////////////////////////////////////////////////////////////////////////////////
//
// ------------------------------------------------------------------------------
//   _____      _            _ _
//  |  _  |    | |          | (_)
//  | |/' | ___| |_ ___   __| |_  ___ ___
//  |  /| |/ __| __/ _ \ / _` | |/ __/ _ \
//  \ |_/ / (__| || (_) | (_| | | (_|  __/
//   \___/ \___|\__\___/ \__,_|_|\___\___|
//
// ------------------------------------------------------------------------------
//
//  Projet de synthèse d'image du Master 2 Informatique spé. Sciences de l'image
//  ~ Thomas DUMONT A.K.A 0ctodice
//
// ------------------------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////////////////////

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
#include <glimac/Player.hpp>
#include <glimac/Monster.hpp>
#include <glimac/HUD.hpp>
#include <memory>

using namespace glimac;

struct Vertex3DText
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 textureCoord;

    Vertex3DText() {}
    Vertex3DText(glm::vec3 pos, glm::vec3 nor, glm::vec3 tex) : position{pos}, normal{nor}, textureCoord{tex} {}
};

enum GAMESTATE
{
    STARTING_SCREEN,
    GATHERING_DATA,
    STARTING_A_LEVEL,
    PLAYING,
    DEATH,
    WINNING
};

int main(int argc, char **argv)
{
    GAMESTATE game = STARTING_SCREEN;

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 900;
    const float GAME_ZONE_WIDTH = 1280;
    const float GAME_ZONE_HEIGHT = 720;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Dungeon Master");

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
    GLint uLightPosLocation = glGetUniformLocation(program.getGLId(), "uLightPos");

    // CREATION DU PLAYER

    Player player;

    // CREATION DU HUD

    HUD hud{WINDOW_WIDTH, WINDOW_HEIGHT, player.getInventory(), player.getMoney(), player.getPVMax(), player.getPV()};

    // CREATION DES BUFFERS

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE_COORDINATE = 2;

    GLuint vbo;
    GLuint vao;
    GLuint fbo;

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

    // ELEMENTS DE BASE

    std::string dataFile = argv[1];
    DataParser data = {"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/data/" + dataFile};
    PPMParser mapParsed;
    MapGenerator map{&windowManager};
    SixAdjacencyCamera camera;

    glm::mat4 globalProjectionMatrix;
    glm::mat4 globalMVMatrix;
    glm::mat4 hudProjectionMatrix = glm::scale(glm::mat4{1.f}, glm::vec3{1.f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 1.f});
    glm::mat4 hudMVMatrix = glm::mat4{1.f};

    glm::vec2 playerDirection;
    float angle;

    float time;
    int currentPlayerPV = *(player.getPV());

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
            if (e.type == SDL_KEYDOWN && game == PLAYING)
            {
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
                case SDLK_i:
                    player.displayInfos();
                    break;
                case SDLK_h:
                    player.takeDamage(player.getCa() + 1);
                    break;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                switch (game)
                {
                case STARTING_SCREEN:
                case DEATH:
                    game = GATHERING_DATA;
                    break;
                case STARTING_A_LEVEL:
                    game = PLAYING;
                    break;
                case WINNING:
                    done = true;
                    break;
                case PLAYING:
                    Treasure *treasurePtr = data.findTreasure(camera.getFrontTile());
                    Monster *monsterPtr = data.findMonster(camera.getFrontTile());
                    if (treasurePtr != nullptr)
                    {
                        switch (treasurePtr->getType())
                        {
                        case 1:
                            player.setMoney(treasurePtr->getValue());
                            break;
                        case 2:
                            player.setPV(treasurePtr->getValue());
                            break;
                        case 3:
                            player.setPVMax(treasurePtr->getValue());
                            break;
                        case 4:
                        {
                            auto old = player.getOffensive();
                            if (old.getName() != "fist")
                            {
                                old.setPosition(treasurePtr->getPosition());
                                data.addTreasure(old);
                            }

                            player.setOffensive(*treasurePtr);
                            break;
                        }
                        case 5:
                        {
                            auto old = player.getDefensive();
                            if (old.getName() != "skin")
                            {
                                old.setPosition(treasurePtr->getPosition());
                                data.addTreasure(old);
                            }
                            player.setDefensive(*treasurePtr);
                            break;
                        }
                        }
                        delete (treasurePtr);
                    }
                    else if (monsterPtr != nullptr)
                    {
                        monsterPtr->takeDamage(player.getAtk());
                    }
                    else if (camera.getPlayerPosition() == map.getEndPosition())
                    {
                        if (*(player.getMoney()) >= data.getGoal())
                            map.openDoor();
                    }
                    break;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);

        MatrixManager matrix{&hudProjectionMatrix, hudMVMatrix};

        switch (game)
        {
        case STARTING_SCREEN:
            hud.drawSplashScreen(0, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix, hudMVMatrix);
            break;
        case STARTING_A_LEVEL:
            hud.drawSplashScreen(1, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix, hudMVMatrix);
            matrix.scale(glm::vec3{0.2});
            matrix.translate(glm::vec3(0.f, 0.f, -1.f));
            hud.drawNumber(std::to_string(data.getGoal()), matrix, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix);
            break;
        case DEATH:
            hud.drawSplashScreen(2, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix, hudMVMatrix);
            break;
        case WINNING:
            hud.drawSplashScreen(3, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix, hudMVMatrix);
            break;
        case GATHERING_DATA:
            // GENERATION DE LA MAP
            mapParsed = {"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/map/" + data.getMapFile()};
            map.setMapToParsed(&mapParsed);

            data.updateData(map.getStartPosition());

            // CREATION DES MATRIX

            globalProjectionMatrix = glm::perspective(glm::radians(70.f), (float)GAME_ZONE_WIDTH / (float)GAME_ZONE_HEIGHT, .1f, 100.f);
            globalMVMatrix = glm::mat4{1.f};

            playerDirection = map.getFirstDirection();
            angle = 90.f * playerDirection.x + 180.f * (playerDirection.y > 0);

            globalMVMatrix = glm::rotate(globalMVMatrix, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));

            // CREATION DE LA CAMERA

            camera = {playerDirection, &globalMVMatrix, &map};

            time = 0.f;

            if (*(player.getPV()) <= 0)
            {
                player.setPV(currentPlayerPV);
            }
            currentPlayerPV = *(player.getPV());

            game = STARTING_A_LEVEL;
            break;
        case PLAYING:
            time = windowManager.getTime();

            glViewport(0, WINDOW_HEIGHT - GAME_ZONE_HEIGHT, GAME_ZONE_WIDTH, GAME_ZONE_HEIGHT);

            data.idle(time, &player, &camera, &map);
            map.idle(camera.getPlayerPosition());
            map.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &globalProjectionMatrix, globalMVMatrix);
            data.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &globalProjectionMatrix, globalMVMatrix);

            glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

            hud.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, &hudProjectionMatrix, hudMVMatrix);

            if (player.isDead())
            {
                game = DEATH;
            }
            else if (camera.getPlayerPosition() == map.getDoorPosition())
            {
                player.setMoney(data.getGoal() * -1);
                game = data.nextLevel() ? WINNING : GATHERING_DATA;
            }
            break;
        }

        glBindVertexArray(0);
        windowManager.swapBuffers();
    }

    // NETTOYAGE
    glDeleteFramebuffers(GL_DRAW_FRAMEBUFFER, &fbo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    hud.clean();
    data.clean();
    map.clean();

    return EXIT_SUCCESS;
}
