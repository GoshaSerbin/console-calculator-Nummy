#pragma once

#include "IExpressionTokenizer.hpp"

namespace Nummy {

    class ExpressionTokenizer : public IExpressionTokenizer {
     public:
        [[nodiscard]] auto tokenize(const std::string& expression, const std::vector<Token>& validTokenList) -> std::vector<Token> override;
    };

}  // namespace Nummy
