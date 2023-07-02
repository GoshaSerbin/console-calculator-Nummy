#pragma once

#include "ITokensManager.hpp"

namespace Nummy {

    class TokensManager : public ITokensManager {
     public:
        TokensManager();
        [[nodiscard]] auto getTokens() -> const std::vector<Token>& override;
        auto addToken(const Token& token) -> void override;

     private:
        std::vector<Token> m_tokens;
    };

}  // namespace Nummy
