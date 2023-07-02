#pragma once

#include "ICalculatable.hpp"
#include "ICalculatableTree.hpp"
#include "IVariablesManager.hpp"
#include "MathDictionary.hpp"

namespace Nummy {

    class CalculatableTree : public ICalculatableTree {
     public:
        CalculatableTree(IVariablesManager& variableManager);
        auto build(const std::vector<Token>& tokens) -> void override;
        [[nodiscard]] auto calculate() -> double override;

     private:
        auto buildWithPriority(OperationPriority priority, std::vector<Token>& leftTokens) -> ICalculatableUPtr;

        IVariablesManager& m_variablesManager;
        ICalculatableUPtr m_root;
    };

}  // namespace Nummy
