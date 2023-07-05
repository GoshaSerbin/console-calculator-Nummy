#include "VariablesManager.hpp"

namespace Nummy {

    VariablesManager::VariablesManager(ITokensManager& tokensManager) : m_tokensManager(tokensManager) {}

    auto VariablesManager::setVariable(const std::string& name, double value) -> void {
        if (!m_values.contains(name)) {
            m_tokensManager.addToken(Token{name, TokenType::Variable});
        }
        m_values[name] = value;
    }

    auto VariablesManager::getVariable(const std::string& name) -> double {
        return m_values.at(name);
    }

}  // namespace Nummy
