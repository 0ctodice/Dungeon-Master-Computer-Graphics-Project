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
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>

namespace glimac
{
    struct RGB
    {
        int r, g, b;
        RGB(){};
        RGB(int red, int green, int blue) : r{red}, g{green}, b{blue} {}
        bool operator==(const RGB &other)
        {
            return r == other.r && g == other.g && b == other.b;
        }
    };

    class PPMParser
    {
    private:
        int width;
        int height;
        std::vector<RGB> pixels;
        void check_comment(std::ifstream &f)
        {
            if (f.peek() == '#')
            {
                std::string yolo;
                std::getline(f, yolo);
            }
        }

    public:
        PPMParser() {}
        PPMParser(std::string path);

        int getWidth() const;
        int getHeight() const;
        std::vector<RGB> getPixels() const;
    };
}