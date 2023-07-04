/*!
    \file
    \brief Header file with constants.

    This header file contains reserved mathematical symbols, default valid tokens, default mathematical constants, operation priorities.
*/

#pragma once

#include "Token.hpp"

#include <unordered_map>
#include <vector>

namespace Nummy {

    namespace ReservedSymbols {

        inline const std::string plus = "+";
        inline const std::string minus = "-";
        inline const std::string product = "*";
        inline const std::string divide = "/";
        inline const std::string exponentiate = "^";
        inline const std::string abs = "abs";
        inline const std::string sqrt = "sqrt";
        inline const std::string atan = "atan";

        inline const std::string openBracket = "(";
        inline const std::string closeBracket = ")";

        inline const std::string assign = "=";

    }  // namespace ReservedSymbols

    namespace Constants {

        inline const std::string pi = "pi";
        inline const std::string e = "e";

    }  // namespace Constants

    inline const std::vector<Token> reservedTokens = {
        {ReservedSymbols::plus,         TokenType::BinaryOperation},
        {ReservedSymbols::minus,        TokenType::BinaryOperation},
        {ReservedSymbols::product,      TokenType::BinaryOperation},
        {ReservedSymbols::divide,       TokenType::BinaryOperation},
        {ReservedSymbols::exponentiate, TokenType::BinaryOperation},
        {ReservedSymbols::openBracket,  TokenType::OpenBracket    },
        {ReservedSymbols::closeBracket, TokenType::CloseBracket   },
        {ReservedSymbols::plus,         TokenType::UnaryOperation },
        {ReservedSymbols::minus,        TokenType::UnaryOperation },
        {ReservedSymbols::abs,          TokenType::UnaryOperation },
        {ReservedSymbols::sqrt,         TokenType::UnaryOperation },
        {ReservedSymbols::atan,         TokenType::UnaryOperation },
        {ReservedSymbols::assign,       TokenType::Asign          },
    };

    using OperationPriority = int;

    /// The higher number means that operation will be calculated earlier
    inline const std::unordered_map<std::string, OperationPriority> operationsPriority{
        {ReservedSymbols::plus,         1},
        {ReservedSymbols::minus,        1},
        {ReservedSymbols::product,      2},
        {ReservedSymbols::divide,       2},
        {ReservedSymbols::exponentiate, 3},
        {ReservedSymbols::abs,          4},
        {ReservedSymbols::sqrt,         4},
        {ReservedSymbols::atan,         4},
    };

}  // namespace Nummy
