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

#include "glimac/common.hpp"

namespace glimac
{
    class Tile
    {
    private:
        glm::vec2 position;
        bool rendered = false;

    public:
        Tile(glm::vec2 pos) : position{pos} {}

        bool operator<(const Tile &other) const
        {
            if (position.x < other.position.x)
            {
                return true;
            }
            return position.y < other.position.y;
        }

        bool operator==(const Tile &other) const
        {
            return other.position == position;
        }

        void setPosition(glm::vec2 pos) { position = pos; }
        glm::vec2 getPosition() const { return position; }
        bool shouldRender() const { return rendered; }
        void changeRender(bool should) { rendered = should; }
    };

}