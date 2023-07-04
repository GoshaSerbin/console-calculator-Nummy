#pragma once

#include "IExpressionTokenizer.hpp"

namespace Nummy {

    /*!
        \brief Realization of IExpressionTokenizer

        This realization does not validate the expression, so expression must be correct (meaning that it consist of valid tokens only).
        \warning  If expression has invalid token then tokenize method will never be completed.

        This realization differs unary and binary operations with same symbols.

        This realization supports tokenization with tokens with same prefix, for example var and var2.

        \warning Spaces does not count as a tokens and are ignored anyway.
    */
    class ExpressionTokenizer : public IExpressionTokenizer {
     public:
        /*!
        \return tokenized expression.
        */
        [[nodiscard]] auto tokenize(const std::string& expression, const std::vector<Token>& validTokenList) -> std::vector<Token> override;
    };

}  // namespace Nummy
