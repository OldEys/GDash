#include"../headers/Exceptions.h"

Font_error::Font_error(const std::string &path) : Exception(std::string("Could not load the font " + path)) {
}

Texture_error::Texture_error(const std::string &path) : Exception(std::string("Could not load the texture " + path)) {
}

Sound_error::Sound_error(const std::string &path) : Exception(std::string("Could not load the sound " + path)) {
}

InputFile_error::InputFile_error(const std::string &path) : Exception(
    std::string("Could not load the input file " + path)) {
}
