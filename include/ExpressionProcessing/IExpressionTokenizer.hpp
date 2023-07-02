#pragma once

#include "Token.hpp"

#include <string>
#include <vector>

namespace Nummy {

    class IExpressionTokenizer {
     public:
        virtual auto tokenize(const std::string& expression, const std::vector<Token>& validTokenList) -> std::vector<Token> = 0;
        virtual ~IExpressionTokenizer() {}
    };

}  // namespace Nummy
