#include <glimac/common.hpp>
#include <glimac/PPMParser.hpp>

namespace glimac
{
    PPMParser::PPMParser(std::string path)
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
        // RECUP DES DIMENSIONS
        check_comment(file);
        parser = "";
        std::getline(file, parser, ' ');
        width = std::stoi(parser);
        parser = "";
        std::getline(file, parser, '\n');
        height = std::stoi(parser);
        // RECUPERATION DE LA VALEUR MAX
        check_comment(file);
        std::getline(file, parser);
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

    int PPMParser::getWidth() const { return width; }
    int PPMParser::getHeight() const { return height; }
    std::vector<RGB> PPMParser::getPixels() const { return pixels; }
}