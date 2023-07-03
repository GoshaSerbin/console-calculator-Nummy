#include "ExpressionTokenizer.hpp"
#include "MathDictionary.hpp"

#include <algorithm>
#include <iostream>

namespace Nummy {

    namespace {

        auto nextOperationCanNotBeBinary(const std::vector<Token>& tokens) -> bool {
            return tokens.size() == 0 || tokens.back().name == ReservedSymbols::openBracket;
        }

    }  // namespace

    auto ExpressionTokenizer::tokenize(const std::string& expression, const std::vector<Token>& validTokenList) -> std::vector<Token> {
        std::vector<Token> tokens{};
        std::string str = expression;
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

        auto orderedValidTokenList = validTokenList;
        std::sort(orderedValidTokenList.begin(), orderedValidTokenList.end(),
                  [](const Token& l, const Token& r) { return l.name.size() > r.name.size(); });

        size_t beginPos = str.find(ReservedSymbols::assign);
        if (beginPos != std::string::npos) {
            tokens.emplace_back(str.substr(0, beginPos), TokenType::Variable);
            tokens.emplace_back(ReservedSymbols::assign, TokenType::Asign);
            beginPos++;

        } else {
            beginPos = 0;
        }

        for (size_t pos = beginPos; pos < str.size();) {
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
        }

        return tokens;
    }

}  // namespace Nummy
