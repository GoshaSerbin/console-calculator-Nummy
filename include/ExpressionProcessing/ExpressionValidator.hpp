#pragma once

#include "IExpressionValidator.hpp"

namespace Nummy {

    /*!
        \brief Realization of IExpressionValidator.
        \warning Possibly some checks are missing.

        This validator checks some properties of the expression. See ExpressionValidator tests for examples.
    */
    class ExpressionValidator : public IExpressionValidator {
     public:
        [[nodiscard]] auto isValid(std::string expression, const std::vector<Token>& validTokenList) -> bool override;

        /*!
            \return info about first found mistake
        */
        [[nodiscard]] auto getMessage() const -> std::string override;

     private:
        [[nodiscard]] auto hasValidBracketSequence(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto isEmpty(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto hasCorrectNumbers(const std::string& expression) noexcept -> bool;
        [[nodiscard]] auto hasCorrectTokens(const std::string& expression, const std::vector<Token>& validTokenList) -> bool;

        std::string m_message;  /// stores info about mistake
    };

}  // namespace Nummy
