#include "BasicCalculator.hpp"
#include "CalculatableTree.hpp"
#include "ExpressionTokenizer.hpp"
#include "ExpressionValidator.hpp"
#include "TokensManager.hpp"
#include "VariablesManager.hpp"

#include <gtest/gtest.h>
#include <sstream>

namespace Nummy {

    class BasicCalculatorTest : public testing::Test {
     protected:
        void SetUp() override {
            validator = std::make_unique<ExpressionValidator>();
            tokenizer = std::make_unique<ExpressionTokenizer>();

            tokensManager = std::make_unique<TokensManager>();
            variablesManager = std::make_unique<VariablesManager>(*tokensManager);
            tree = std::make_unique<CalculatableTree>(*variablesManager);
            calculator = std::make_unique<BasicCalculator>(in, out, std::move(validator), std::move(tokenizer), std::move(tree),
                                                           std::move(tokensManager), std::move(variablesManager));
        }
        void TearDown() override {}

        std::unique_ptr<IExpressionValidator> validator;
        std::unique_ptr<IExpressionTokenizer> tokenizer;

        std::unique_ptr<ITokensManager> tokensManager;
        std::unique_ptr<IVariablesManager> variablesManager;
        std::unique_ptr<ICalculatableTree> tree;

        std::stringstream in;
        std::stringstream out;

        std::unique_ptr<ICalculator> calculator;
    };

}  // namespace Nummy
