#include "TextureManager.h"

#include <iostream>

sf::Texture& TextureManager::getTexture(const std::string& name) {
    if(!textures.contains(name)) {
        sf::Texture texture ;
        if(!texture.loadFromFile(name)) {
            std::cerr << "Texture loading error from:" << name <<"\n";
        }
        else {
            std::cout<<"Texture loaded succesfully: "<<name<<"\n";
            std::cout<<"Se incarca din texture manager\n";
        }
        textures[name] = texture;
    }
    return textures.at(name);
}
