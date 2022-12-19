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

#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>
#include <glimac/Character.hpp>
#include <glimac/MapGenerator.hpp>
#include <glimac/SixAdjacencyCamera.hpp>

namespace glimac
{
    class Entity
    {
    protected:
        int id;
        glm::vec2 position;
        glm::vec2 initialPosition;
        int levelStage;
        std::string name;
        std::string textureName;
        Texture texture;
        float rotation = 0.f;

    public:
        Entity() = delete;
        Entity(int id, glm::vec2 pos, glm::vec2 initPos, int lvl, std::string name, std::string texture);
        virtual void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const = 0;
        virtual void updateActions(float time, Character *player, SixAdjacencyCamera *camera, MapGenerator *map);
        void deleteTexture();
        int getId() const;
        glm::vec2 getPosition() const;
        glm::vec2 getInitialPosition() const;
        int getLevelStage() const;
        std::string getName() const;
        Texture getTexture() const;
        std::string getTextureName() const;
    };
}