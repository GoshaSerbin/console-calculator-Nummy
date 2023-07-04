#include "FormatCalculator.hpp"
#include "Formatter.hpp"

#include <sstream>

namespace Nummy {

    FormatCalculator::FormatCalculator(std::istream& in,
                                       std::ostream& out,
                                       std::unique_ptr<IExpressionValidator> validator,
                                       std::unique_ptr<IExpressionTokenizer> tokenizer,
                                       std::unique_ptr<ICalculatableTree> tree,
                                       std::unique_ptr<ITokensManager> tokensManager,
                                       std::unique_ptr<IVariablesManager> variablesManager)
        : BasicCalculator(
              in, out, std::move(validator), std::move(tokenizer), std::move(tree), std::move(tokensManager), std::move(variablesManager)) {
        m_formatter = std::make_unique<Formatter>();
    }

    auto FormatCalculator::setFormatter(std::unique_ptr<IFormatter> formatter) -> void {
        m_formatter = std::move(formatter);
    }

    auto FormatCalculator::inputPrompt(size_t command) -> std::string {
        return "[ in " + std::to_string(command) + " ] : ";
    }

    auto FormatCalculator::outputPrompt(size_t command) -> std::string {
        return "[ out " + std::to_string(command) + "] : ";
    }

    namespace {

        const std::string welcomeMessage = "Welcome to Nummy!";

        template <typename T>
        std::string toString(T val) {
            std::ostringstream oss;
            oss << val;
            return oss.str();
        }

    }  // namespace

    auto FormatCalculator::run() -> void {
        m_out << m_formatter->formate(welcomeMessage, MessageType::Special) << std::endl;

        static size_t commandCounter = 0;
        m_out << m_formatter->formate(inputPrompt(commandCounter), MessageType::Additional);

        std::string expression{};
        while (getline(m_in, expression)) {
            if (expression == m_exitCommand) {
                break;
            }
            if (m_validator && !m_validator->isValid(expression, m_tokensManager->getTokens())) {
                m_out << m_formatter->formate(m_validator->getMessage(), MessageType::Error) << "\n\n";
                m_out << m_formatter->formate(inputPrompt(commandCounter), MessageType::Additional);
                continue;
            }

            std::vector<Token> tokens = m_tokenizer->tokenize(expression, m_tokensManager->getTokens());

            m_tree->build(tokens);

            m_out << m_formatter->formate(outputPrompt(commandCounter), MessageType::Success)
                  << m_formatter->formate(toString(m_tree->calculate()), MessageType::Default) << std::endl;
            ++commandCounter;
            m_out << std::endl << m_formatter->formate(inputPrompt(commandCounter), MessageType::Additional);
        }
    }

}  // namespace Nummy
