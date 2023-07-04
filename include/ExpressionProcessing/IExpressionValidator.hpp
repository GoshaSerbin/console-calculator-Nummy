#pragma once

#include "Token.hpp"

#include <vector>

namespace Nummy {

    /*!
        \brief The purpose of this class is to validate the expression using valid tokens.
    */
    class IExpressionValidator {
     public:
        virtual auto isValid(std::string expression, const std::vector<Token>& validTokenList) -> bool = 0;

        /*!
            \return information in case expression is not valid
        */
        virtual auto getMessage() const -> std::string = 0;

        virtual ~IExpressionValidator() {}
    };

}  // namespace Nummy
