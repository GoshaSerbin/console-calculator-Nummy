#include "CalculatableTree.hpp"
#include "CalculatableMaker.hpp"
#include "MathDictionary.hpp"

namespace Nummy {

    CalculatableTree::CalculatableTree(IVariablesManager& variablesManager) : m_variablesManager(variablesManager) {}

    auto CalculatableTree::build(const std::vector<Token>& tokens) -> void {
        auto leftTokens = tokens;
        m_root = buildWithPriority(0, leftTokens);
    }

    namespace {

        auto findRelatedCloseBracket(std::vector<Token>& tokens) -> std::vector<Nummy::Token>::iterator {
            size_t count = 1;
            std::vector<Nummy::Token>::iterator closeBracketIter = tokens.begin();
            while (count != 0) {
                if (closeBracketIter->type == TokenType::OpenBracket) {
                    count++;
                }
                if (closeBracketIter->type == TokenType::CloseBracket) {
                    count--;
                }
                closeBracketIter++;
            }
            return closeBracketIter;
        }

    }  // namespace

    auto CalculatableTree::buildWithPriority(OperationPriority priority, std::vector<Token>& leftTokens) -> ICalculatableUPtr {
        ICalculatableUPtr subRoot;

        while (leftTokens.size() > 0) {
            auto token = *leftTokens.begin();

            switch (token.type) {
                case TokenType::Number:
                    leftTokens.erase(leftTokens.begin());
                    subRoot = CalculatableMaker::makeNumber(std::stod(token.name));
                    break;

                case TokenType::OpenBracket: {
                    leftTokens.erase(leftTokens.begin());
                    auto closeBracketIter = findRelatedCloseBracket(leftTokens);
                    std::vector<Token> tokensInBrackets(leftTokens.begin(), closeBracketIter);
                    subRoot = std::move(buildWithPriority(0, tokensInBrackets));
                    leftTokens.erase(leftTokens.begin(), closeBracketIter);
                    break;
                }

                case TokenType::CloseBracket:
                    leftTokens.erase(leftTokens.begin());
                    break;

                case TokenType::BinaryOperation: {
                    const OperationPriority newPriority = operationsPriority.at(token.name);
                    if (newPriority > priority) {
                        leftTokens.erase(leftTokens.begin());
                        subRoot = CalculatableMaker::makeBinaryOperation(token.name, std::move(subRoot),
                                                                         std::move(buildWithPriority(newPriority, leftTokens)));
                    } else {
                        return subRoot;
                    }
                    break;
                }

                case TokenType::UnaryOperation: {
                    const OperationPriority newPriority = operationsPriority.at(token.name);
                    if (newPriority > priority) {
                        leftTokens.erase(leftTokens.begin());
                        subRoot = CalculatableMaker::makeUnaryOperation(token.name, std::move(buildWithPriority(newPriority, leftTokens)));
                    } else {
                        return subRoot;
                    }
                    break;
                }

                case TokenType::Variable:
                    // todo no need to check, its work of validator
                    if (std::next(leftTokens.begin()) != leftTokens.end() && std::next(leftTokens.begin())->type == TokenType::Asign) {
                        leftTokens.erase(leftTokens.begin());
                        leftTokens.erase(leftTokens.begin());
                        double value = buildWithPriority(0, leftTokens)->calculate();
                        subRoot = CalculatableMaker::makeNumber(value);
                        m_variablesManager.setVariable(token.name, value);
                        return subRoot;
                    } else {
                        leftTokens.erase(leftTokens.begin());
                        double value = m_variablesManager.getVariable(token.name);
                        subRoot = CalculatableMaker::makeNumber(value);
                    }
                    break;
                default:
                    break;
            }
        }
        return subRoot;
    }

    auto CalculatableTree::calculate() -> double {
        return m_root->calculate();
    }

}  // namespace Nummy
