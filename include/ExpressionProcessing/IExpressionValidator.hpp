#pragma once

#include "Token.hpp"

#include <vector>

namespace Nummy {

    class IExpressionValidator {
     public:
        virtual auto isValid(std::string expression, const std::vector<Token>& validTokenList) -> bool = 0;
        virtual auto getMessage() const -> std::string = 0;
        virtual ~IExpressionValidator() {}
    };

}  // namespace Nummy
