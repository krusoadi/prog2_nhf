#ifndef PROG2_NHF_EXCEPTIONS_HPP
#define PROG2_NHF_EXCEPTIONS_HPP

#include <exception>
#include <string>
enum errors {
    GenericError,
    NotDefinedError,
    NegativeMoney,
    NotEnoughShares,
    WrongMaster,
    OverIndex,
    EmptyContainer,
    NegativeIndex
};

class Exceptions : public std::exception {
    errors type;
    std::string msg;
public:
    explicit Exceptions(errors errorType, const char* message = "");
    [[nodiscard]] const char* what() const noexcept override;

};


#endif //PROG2_NHF_EXCEPTIONS_HPP
