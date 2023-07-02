#pragma once

#include "ICalculatableTree.hpp"
#include "ICalculator.hpp"
#include "IExpressionTokenizer.hpp"
#include "IExpressionValidator.hpp"
#include "ITokensManager.hpp"
#include "IVariablesManager.hpp"

#include <iostream>
#include <memory>

namespace Nummy {

    /*!
    \brief class gives basic functionality of calculator

    It can read input from std::istream, write output to any std::ostream. Variables can be added.
    */
    class BasicCalculator : public ICalculator {
     public:
        BasicCalculator(std::istream& in,
                        std::ostream& out,
                        std::unique_ptr<IExpressionValidator> validator,
                        std::unique_ptr<IExpressionTokenizer> tokenizer,
                        std::unique_ptr<ICalculatableTree> tree,
                        std::unique_ptr<ITokensManager> tokensManager,
                        std::unique_ptr<IVariablesManager> variablesManager);
        virtual auto run() -> void override;

     protected:
        std::istream& m_in;
        std::ostream& m_out;

        std::unique_ptr<IExpressionValidator> m_validator;
        std::unique_ptr<IExpressionTokenizer> m_tokenizer;

        std::unique_ptr<ICalculatableTree> m_tree;

        std::unique_ptr<ITokensManager> m_tokensManager;
        std::unique_ptr<IVariablesManager> m_variablesManager;
    };

}  // namespace Nummy
