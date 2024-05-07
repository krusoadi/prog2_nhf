#ifndef PROG2_NHF_EXCEPTIONS_HPP
#define PROG2_NHF_EXCEPTIONS_HPP

#include <exception>

enum errors {
    GenericError,
    NotDefinedError,
    NegativeMoney,
    NotEnoughShares,
    WrongMaster
};

class Exceptions : public std::exception {
    errors type;
    const char* msg;
public:
    explicit Exceptions(errors errorType, const char* message = "");
    const char* what() const noexcept override;

};


#endif //PROG2_NHF_EXCEPTIONS_HPP
