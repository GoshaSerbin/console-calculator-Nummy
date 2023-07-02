#pragma once

#include "Token.hpp"

#include <vector>

namespace Nummy {

    class ICalculatableTree {
     public:
        virtual auto build(const std::vector<Token>& tokens) -> void = 0;
        virtual auto calculate() -> double = 0;
        virtual ~ICalculatableTree() {}
    };

}  // namespace Nummy
