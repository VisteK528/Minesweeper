#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class BaseException: public std::exception
{
    private:
        std::string msg;
    public:
        BaseException(const std::string& message): msg(message){};
        const char* what() const noexcept {return msg.c_str();}
};

class TexturesLoadingError: public BaseException
{
    public:
        TexturesLoadingError(const std::string& message): BaseException(message){};
};

class FontLoadingError: public BaseException
{
    public:
        FontLoadingError(const std::string& message): BaseException(message){};
};

#endif