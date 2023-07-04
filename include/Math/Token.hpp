#pragma once

#include <iostream>
#include <string>

namespace Nummy {

    /// \todo Functions support are not implemented yet.
    enum class TokenType {
        Number,
        UnaryOperation,
        BinaryOperation,
        OpenBracket,
        CloseBracket,
        Asign,
        Variable,
        Function
    };

    /// \brief Basic element of any expression.
    class Token {
     public:
        Token(const std::string& name, TokenType type) : name(name), type(type){};

        friend auto operator==(const Token& l, const Token& r) -> bool { return l.name == r.name && l.type == r.type; }
        friend std::ostream& operator<<(std::ostream& os, const Token& token) {
            os << "{\"" << token.name << "\", " << static_cast<int>(token.type) << "}";
            return os;
        }

        std::string name;
        TokenType type;
    };

}  // namespace Nummy
