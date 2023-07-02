#pragma once

#include "ITokensManager.hpp"
#include "IVariablesManager.hpp"

#include <unordered_map>

namespace Nummy {

    class VariablesManager : public IVariablesManager {
     public:
        VariablesManager(ITokensManager& tokensManager);

        auto setVariable(const std::string& name, double value) -> void override;
        [[nodiscard]] auto getVariable(const std::string& name) -> double override;

     private:
        std::unordered_map<std::string, double> m_values;
        ITokensManager& m_tokensManager;
    };

}  // namespace Nummy
