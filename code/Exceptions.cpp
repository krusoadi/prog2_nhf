#include "../headers/Exceptions.hpp"

Exceptions::Exceptions(errors errorType, const char *message) : type(errorType), msg(message) {}

const char *Exceptions::what() const noexcept {
    return this->msg.c_str(); // due to std::string <--> const char* conversion
}

