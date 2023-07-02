// todo: replace abs, sqrt and other functions

#pragma once

#include "ICalculatable.hpp"

#include <cmath>

namespace Nummy {

    class UnaryOperation : public ICalculatable {
     public:
        explicit UnaryOperation(ICalculatableUPtr argument) : m_argument(std::move(argument)) {}

     protected:
        ICalculatableUPtr m_argument;
    };

    class Minus : public UnaryOperation {
     public:
        explicit Minus(ICalculatableUPtr argument) : UnaryOperation(std::move(argument)) {}

        auto calculate() const -> double override { return -m_argument->calculate(); }
    };

    class Plus : public UnaryOperation {
     public:
        explicit Plus(ICalculatableUPtr argument) : UnaryOperation(std::move(argument)) {}

        auto calculate() const -> double override { return m_argument->calculate(); }
    };

    class Abs : public UnaryOperation {
     public:
        explicit Abs(ICalculatableUPtr argument) : UnaryOperation(std::move(argument)) {}

        auto calculate() const -> double override { return std::abs(m_argument->calculate()); }
    };

    class Atan : public UnaryOperation {
     public:
        explicit Atan(ICalculatableUPtr argument) : UnaryOperation(std::move(argument)) {}

        auto calculate() const -> double override { return std::atan(m_argument->calculate()); }
    };

    class Sqrt : public UnaryOperation {
     public:
        explicit Sqrt(ICalculatableUPtr argument) : UnaryOperation(std::move(argument)) {}

        auto calculate() const -> double override { return std::sqrt(m_argument->calculate()); }
    };

}  // namespace Nummy
