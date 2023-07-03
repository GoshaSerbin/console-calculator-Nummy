#pragma once

#include "IExpressionValidator.hpp"

namespace Nummy {

    class ExpressionValidator : public IExpressionValidator {
     public:
        [[nodiscard]] auto isValid(std::string expression, const std::vector<Token>& validTokenList) -> bool override;
        [[nodiscard]] auto getMessage() const -> std::string override;

     private:
        [[nodiscard]] auto hasValidBracketSequence(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto isEmpty(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto hasCorrectNumbers(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto hasCorrectTokens(const std::string& expression, const std::vector<Token>& validTokenList) -> bool;

        std::string m_message;
    };

}  // namespace Nummy
