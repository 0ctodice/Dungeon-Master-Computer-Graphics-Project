#pragma once

#include "glm.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glimac/FilePath.hpp>
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
        PPMParser(std::string path)
        {
            // CREATION DU STREAM
            std::ifstream file(path, std::ios::in);
            if (file.fail())
            {
                std::cout << "Could not open file: " << path << std::endl;
                return;
            }
            // RECUP DU MODE
            check_comment(file);
            std::string parser;
            std::getline(file, parser);
            std::cout << parser << std::endl;
            // RECUP DES DIMENSIONS
            check_comment(file);
            parser = "";
            std::getline(file, parser, ' ');
            width = std::stoi(parser);
            std::cout << "width=" << width << std::endl;
            parser = "";
            std::getline(file, parser, '\n');
            height = std::stoi(parser);
            std::cout << "height=" << height << std::endl;
            // RECUPERATION DE LA VALEUR MAX
            check_comment(file);
            std::getline(file, parser);
            std::cout << parser << std::endl;
            check_comment(file);
            parser = "";
            for (int i = 0; i < width * height * 3; i += 3)
            {
                std::string r, g, b;
                std::getline(file, r);
                std::getline(file, g);
                std::getline(file, b);
                RGB pixel(std::stoi(r), std::stoi(g), std::stoi(b));
                pixels.push_back(pixel);
            }
            file.close();
        }

        int getWidth() const { return width; }
        int getHeight() const { return height; }
        std::vector<RGB> getPixels() const { return pixels; }
    };
}