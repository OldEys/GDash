#include "../headers/TextureManager.h"
#include "../headers/Exceptions.h"

sf::Texture &TextureManager::getTexture(const std::string &name) {
    if (!textures.contains(name)) {
        sf::Texture texture;
        if (!texture.loadFromFile(name)) {
            throw Texture_error(name);
        }

        textures[name] = texture;
    }
    return textures.at(name);
}
