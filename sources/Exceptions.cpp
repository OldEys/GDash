#include"../headers/Exceptions.h"

Font_error::Font_error(std::string path) : Exception("Could not load the font " + path) {
}

Texture_error::Texture_error(std::string path) : Exception("Could not load the texture " + path) {
}

Sound_error::Sound_error(std::string path) : Exception("Could not load the sound " + path) {
}

InputFile_error::InputFile_error(std::string path) : Exception(
    "Could not load the input file " + path) {
}
