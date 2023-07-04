#pragma once

#include "ITokensManager.hpp"

namespace Nummy {

    /// \warning addToken method does not validate added token (in case its name contains reserved symbols).
    class TokensManager : public ITokensManager {
     public:
        TokensManager();
        [[nodiscard]] auto getTokens() -> const std::vector<Token>& override;
        auto addToken(const Token& token) -> void override;

     private:
        std::vector<Token> m_tokens;
    };

}  // namespace Nummy
