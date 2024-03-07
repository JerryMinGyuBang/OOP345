#pragma once
#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    std::string message;
public:
    // Constructor accepts a string message
    CustomException(const std::string& msg)
    {
        message = msg;
    }

    // Override the what() method from std::exception
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};
