#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include<string>
class TextureManager {
    std::unordered_map<std::string, sf::Texture> textures;

public:
    sf::Texture& getTexture(const std::string& name);
};



#endif //TEXTUREMANAGER_H
