#include"../headers/Exceptions.h"

Font_error::Font_error(const std::string &path) : Exception(std::string("Could not load the font ").append(path)) {
}

Texture_error::Texture_error(const std::string& path) : Exception(std::string("Could not load the texture ").append(path) ) {
}

Sound_error::Sound_error(const std::string& path) : Exception(std::string("Could not load the sound ").append(path) ) {
}

InputFile_error::InputFile_error(const std::string& path) :Exception(std::string("Could not load the input file ").append(path) ) {
}
