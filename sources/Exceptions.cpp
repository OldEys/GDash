#include"../headers/Exceptions.h"
#include<string>

Font_error::Font_error(const std::string &path) : ApplicationException(
    std::string("Could not load the font ").append(path)) {
}

Texture_error::Texture_error(const std::string &path) : ApplicationException(
    std::string("Could not load the texture ").append(path)) {
}

Sound_error::Sound_error(const std::string &path) : ApplicationException(
    std::string("Could not load the sound ").append(path)) {
}

InputFile_error::InputFile_error(const std::string &path) : ApplicationException(
    std::string("Could not load the input file ").append(path)) {
}
InvalidLevelIndex_error::InvalidLevelIndex_error(const std::string &index) : ApplicationException(
    std::string("Could not find the level index").append(index)) {
}
