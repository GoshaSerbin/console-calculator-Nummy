#pragma once

#include "ICalculatable.hpp"

namespace Nummy {

    class CalculatableMaker {
     public:
        [[nodiscard]] static auto makeBinaryOperation(const std::string& name, ICalculatableUPtr left, ICalculatableUPtr right)
            -> ICalculatableUPtr;
        [[nodiscard]] static auto makeUnaryOperation(const std::string& name, ICalculatableUPtr argument) -> ICalculatableUPtr;
        [[nodiscard]] static auto makeNumber(double number) -> ICalculatableUPtr;
    };

}  // namespace Nummy
