
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<stdexcept>

class ApplicationException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Font_error : public ApplicationException {
public:
    explicit Font_error(const std::string &path);
};

class Texture_error : public ApplicationException {
public:
    explicit Texture_error(const std::string &path);
};

class Sound_error : public ApplicationException{
public:
    explicit Sound_error(const std::string &path);
};

class InputFile_error : public ApplicationException{
public:
    explicit InputFile_error(const std::string &path);
};

#endif //EXCEPTIONS_H
