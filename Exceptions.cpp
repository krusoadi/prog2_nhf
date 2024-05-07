#include "Exceptions.h"

Exceptions::Exceptions(errors errorType, const char *message) : type(errorType), msg(message) {}

const char *Exceptions::what() const noexcept {
    return this->msg;
}

