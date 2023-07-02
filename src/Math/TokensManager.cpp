#include "TokensManager.hpp"
#include "MathDictionary.hpp"

namespace Nummy {

    TokensManager::TokensManager() {
        m_tokens = reservedTokens;
    }

    auto TokensManager::getTokens() -> const std::vector<Token>& {
        return m_tokens;
    }

    auto TokensManager::addToken(const Token& token) -> void {
        m_tokens.push_back(token);
    }

}  // namespace Nummy
