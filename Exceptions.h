#ifndef PROG2_NHF_EXCEPTIONS_H
#define PROG2_NHF_EXCEPTIONS_H

#include <exception>

enum errors {
    GenericError,
    NotDefinedError,
    NegativeMoney
};

class Exceptions : public std::exception {
    errors type;
    const char* msg;
public:
    explicit Exceptions(errors errorType, const char* message = "");
    const char* what() const noexcept override;

};


#endif //PROG2_NHF_EXCEPTIONS_H
