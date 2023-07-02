#include "BasicCalculator.hpp"

namespace Nummy {

    BasicCalculator::BasicCalculator(std::istream& in,
                                     std::ostream& out,
                                     std::unique_ptr<IExpressionValidator> validator,
                                     std::unique_ptr<IExpressionTokenizer> tokenizer,
                                     std::unique_ptr<ICalculatableTree> tree,
                                     std::unique_ptr<ITokensManager> tokensManager,
                                     std::unique_ptr<IVariablesManager> variablesManager)
        : m_in(in),
          m_out(out),
          m_validator(std::move(validator)),
          m_tokenizer(std::move(tokenizer)),
          m_tree(std::move(tree)),
          m_tokensManager(std::move(tokensManager)),
          m_variablesManager(std::move(variablesManager)) {}

    namespace {

        const std::string welcomeMessage = "Hello!.";
        const std::string exitCommand = "q";

    }  // namespace

    auto BasicCalculator::run() -> void {
        std::string expression{};
        while (getline(m_in, expression)) {
            if (expression == exitCommand) {
                break;
            }
            // if (m_validator && !m_validator->isValid(expression, m_dictionary->getValidTokenList())) {
            //     m_out << m_validator->getMessage() << std::endl;
            //     continue;
            // }

            std::vector<Token> tokens = m_tokenizer->tokenize(expression, m_tokensManager->getTokens());

            // for (auto token : tokens) {
            //     std::cout << token << " ";
            // }

            m_tree->build(tokens);

            m_out << m_tree->calculate() << std::endl;

            // for (auto token : m_dictionary->getValidTokenList()) {
            //     std::cout << token << " ";
            // }
        }
    }

}  // namespace Nummy
