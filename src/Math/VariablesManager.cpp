#include "VariablesManager.hpp"

namespace Nummy {

    VariablesManager::VariablesManager(ITokensManager& tokensManager) : m_tokensManager(tokensManager) {}

    auto VariablesManager::setVariable(const std::string& name, double value) -> void {
        m_values[name] = value;
        m_tokensManager.addToken(Token{name, TokenType::Variable});
    }

    auto VariablesManager::getVariable(const std::string& name) -> double {
        return m_values.at(name);
    }

}  // namespace Nummy
