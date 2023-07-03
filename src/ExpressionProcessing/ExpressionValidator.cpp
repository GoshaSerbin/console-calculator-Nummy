#include "ExpressionValidator.hpp"
#include "MathDictionary.hpp"

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

    // incorrect algorithm
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

        auto hasNumbers(const std::vector<Token>& tokens) -> bool {
            return std::find_if(tokens.begin(), tokens.end(), [](const Token& token) { return token.type == TokenType::Number; }) !=
                   tokens.end();
        }

    }  // namespace

    auto ExpressionValidator::hasCorrectTokens(const std::string& expression, const std::vector<Token>& validTokenList) -> bool {
        std::string str = expression;
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

        auto orderedValidTokenList = validTokenList;
        std::sort(orderedValidTokenList.begin(), orderedValidTokenList.end(),
                  [](const Token& l, const Token& r) { return l.name.size() > r.name.size(); });

        std::vector<Token> tokens{};
        size_t beginPos = str.find("=");
        if (beginPos != std::string::npos) {
            tokens.emplace_back(str.substr(0, beginPos), TokenType::Variable);
            tokens.emplace_back("=", TokenType::Asign);
            beginPos++;

        } else {
            beginPos = 0;
        }

        for (size_t pos = beginPos; pos < str.size();) {
            size_t previosTokensSize = tokens.size();
            for (const auto& token : orderedValidTokenList) {
                if (str.compare(pos, token.name.size(), token.name) == 0) {
                    if (token.type == TokenType::BinaryOperation && nextOperationCanNotBeBinary(tokens)) {
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
                m_message = "Uknown token.";
                return false;
            }
        }

        if (!hasNumbers(tokens)) {
            m_message = "Expression does not have any numbers.";
            return false;
        }

        for (int i = 0; i < tokens.size() - 1; ++i) {
            if (tokens[i].type == TokenType::BinaryOperation && tokens[i + 1].type == TokenType::BinaryOperation) {
                m_message = "Incorrect binary operation.";
                return false;
            }
        }

        return true;
    }

    auto ExpressionValidator::getMessage() const -> std::string {
        return m_message;
    }

}  // namespace Nummy
