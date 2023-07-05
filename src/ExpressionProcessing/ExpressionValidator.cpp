#include "ExpressionValidator.hpp"
#include "MathDictionary.hpp"

#include <algorithm>

namespace Nummy {

    auto ExpressionValidator::isValid(std::string expression, const std::vector<Token>& validTokenList) -> bool {
        expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

        if (!hasValidBracketSequence(expression)) {
            return false;
        }
        if (isEmpty(expression)) {
            return false;
        }
        if (!hasCorrectNumbers(expression)) {
            return false;
        }
        if (!hasCorrectTokens(expression, validTokenList)) {
            return false;
        }
        return true;
    }

    auto ExpressionValidator::hasValidBracketSequence(const std::string& expression) noexcept -> bool {
        int bracketCounter = 0;

        for (size_t i = 0; i < expression.size(); ++i) {
            if (expression[i] == '(') {
                ++bracketCounter;
            }
            if (expression[i] == ')') {
                bracketCounter--;
                if (bracketCounter < 0) {
                    m_message = "Invalid bracket \')\' in " + std::to_string(i) + "th symbol";
                    return false;
                }
            }
        }
        if (bracketCounter > 0) {
            m_message = "To many  \'(\' brackets in expression";
            return false;
        }
        return true;
    }

    auto ExpressionValidator::isEmpty(const std::string& expression) noexcept -> bool {
        if (expression.size() == 0) {
            m_message = "Expression is empty.";
            return true;
        }
        return false;
    }

    auto ExpressionValidator::hasCorrectNumbers(const std::string& expression) noexcept -> bool {
        if (expression[0] == '.' || expression[expression.size() - 1] == '.') {
            m_message = "Incorrect number.";
            return false;
        }
        bool numberHasDot = false;
        for (size_t pos = 1; pos < expression.size() - 1; ++pos) {
            if (expression[pos] == '.') {
                if (numberHasDot) {
                    m_message = "To many dots in number.";
                    return false;
                }
                numberHasDot = true;
                if (!std::isdigit(expression[pos - 1]) || !std::isdigit(expression[pos + 1])) {
                    m_message = "Incorrect number.";
                    return false;
                }
            } else {
                if (!std::isdigit(expression[pos])) {
                    numberHasDot = false;
                }
            }
        }
        return true;
    }

    namespace {

        auto nextOperationCanNotBeBinary(const std::vector<Token>& tokens) -> bool {
            return tokens.size() == 0 || tokens.back().name == ReservedSymbols::openBracket;
        }

        auto hasNumbersOrVariables(const std::vector<Token>& tokens) -> bool {
            return std::find_if(tokens.begin(), tokens.end(), [](const Token& token) {
                       return token.type == TokenType::Number || token.type == TokenType::Variable;
                   }) != tokens.end();
        }

        auto isVariable(const std::string& name) -> bool {
            if (name.empty()) {
                return false;
            }
            for (const auto& token : reservedTokens) {
                if (name.find(token.name) != std::string::npos) {
                    return false;
                }
            }
            if (name.find(".") != std::string::npos) {
                return false;
            }
            if (std::all_of(name.begin(), name.end(), ::isdigit)) {
                return false;
            }
            return true;
        }

    }  // namespace

    auto ExpressionValidator::hasCorrectTokens(const std::string& expression, const std::vector<Token>& validTokenList) -> bool {
        std::string str = expression;
        auto orderedValidTokenList = validTokenList;
        std::sort(orderedValidTokenList.begin(), orderedValidTokenList.end(),
                  [](const Token& l, const Token& r) { return l.name.size() > r.name.size(); });

        std::vector<Token> tokens{};
        size_t assignPos = str.find(ReservedSymbols::assign);
        while (assignPos != std::string::npos) {
            std::string varName = str.substr(0, assignPos);
            if (!isVariable(varName)) {
                m_message = "Incorrect name of variable \'" + varName + "\'.";
                return false;
            }
            tokens.emplace_back(varName, TokenType::Variable);
            tokens.emplace_back(ReservedSymbols::assign, TokenType::Asign);
            str.erase(0, assignPos + 1);
            assignPos = str.find(ReservedSymbols::assign);
        }

        for (size_t pos = 0; pos < str.size();) {
            size_t previosTokensSize = tokens.size();
            for (const auto& token : orderedValidTokenList) {
                if (str.compare(pos, token.name.size(), token.name) == 0) {
                    if (token.type == TokenType::BinaryOperation && nextOperationCanNotBeBinary(tokens)) {
                        continue;
                    }
                    if (token.type == TokenType::UnaryOperation && !nextOperationCanNotBeBinary(tokens)) {
                        continue;
                    }
                    tokens.push_back(token);
                    pos += token.name.size();
                    break;
                }
            }

            if (pos < str.size() && std::isdigit(str[pos])) {
                size_t endPos = pos + 1;
                while (endPos < str.size() && std::isdigit(str[endPos])) {
                    ++endPos;
                }
                if (endPos < str.size() && str[endPos] == '.') {
                    do {
                        ++endPos;
                    } while (endPos < str.size() && std::isdigit(str[endPos]));
                }

                tokens.emplace_back(str.substr(pos, endPos - pos), TokenType::Number);
                pos = endPos;
            }
            if (tokens.size() == previosTokensSize) {
                m_message = "Uknown token at position " + std::to_string(pos) + ".";
                return false;
            }
        }

        if (!hasNumbersOrVariables(tokens)) {
            m_message = "Expression does not have any numbers.";
            return false;
        }

        for (size_t i = 0; i < tokens.size() - 1; ++i) {
            if (tokens[i].type == TokenType::BinaryOperation && tokens[i + 1].type == TokenType::BinaryOperation) {
                m_message = "Incorrect binary operation.";
                return false;
            }
        }

        if (tokens.back().type == TokenType::BinaryOperation) {
            m_message = "Incorrect binary operation at the end.";
            return false;
        }

        return true;
    }

    auto ExpressionValidator::getMessage() const -> std::string {
        return m_message;
    }

}  // namespace Nummy
