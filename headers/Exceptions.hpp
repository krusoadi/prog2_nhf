#ifndef PROG2_NHF_EXCEPTIONS_HPP
#define PROG2_NHF_EXCEPTIONS_HPP

#include <exception>
#include <string>
// Errors used in the program, to get these you have to call e.getType() (e = Exception &e)
enum errors {
    NegativeMoney,
    NotEnoughShares,
    WrongMaster,
    OverIndex,
    EmptyContainer,
    NegativeIndex,
    IDAlreadyExists,
    InvalidId,
    FileError,
    UserNotFound,
    FatalShareError
};

class Exceptions : public std::exception {
    errors type; //  enum errors
    std::string msg; // Message when thrown an Exception
public:
    // Constructor
    explicit Exceptions(errors errorType, const char *message = "");

    // Getters
    [[nodiscard]] const char *what() const noexcept override;
    [[nodiscard]] errors getType() const;
};


#endif //PROG2_NHF_EXCEPTIONS_HPP
