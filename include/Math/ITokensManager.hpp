#pragma once

#include "Token.hpp"

#include <vector>

namespace Nummy {

    /*!
    \brief class is responsable for working with tokens


    */
    class ITokensManager {
     public:
        virtual auto getTokens() -> const std::vector<Token>& = 0;
        virtual auto addToken(const Token& token) -> void = 0;
        virtual ~ITokensManager() {}
    };

}  // namespace Nummy
