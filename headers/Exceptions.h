
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<stdexcept>

class Exception :public std::runtime_error{
    using std::runtime_error::runtime_error;
};
class Font_error:public Exception{
public:
    explicit Font_error(std::string path);
};
class Texture_error:public Exception {
public:
    explicit Texture_error(std::string path);
};
class Sound_error:public Exception {
public:
    explicit Sound_error(std::string path);
};
class InputFile_error:public Exception {
public:
    explicit InputFile_error(std::string path);
};

#endif //EXCEPTIONS_H
