/*!
\file
\brief Заголовочный файл с описанием классов

Данный файл содержит в себе определения основных
классов, используемых в демонстрационной программе
*/
// todo: логарифм

#pragma once

#include "ICalculatable.hpp"

#include <cmath>

namespace Nummy {

    class BinaryOperation : public ICalculatable {
     public:
        explicit BinaryOperation(ICalculatableUPtr left, ICalculatableUPtr right) : m_left(std::move(left)), m_right(std::move(right)) {}

     protected:
        ICalculatableUPtr m_left;
        ICalculatableUPtr m_right;
    };

    class Add : public BinaryOperation {
     public:
        explicit Add(ICalculatableUPtr left, ICalculatableUPtr right) : BinaryOperation(std::move(left), std::move(right)) {}

        auto calculate() const -> double override { return m_left->calculate() + m_right->calculate(); }
    };

    class Subtract : public BinaryOperation {
     public:
        explicit Subtract(ICalculatableUPtr left, ICalculatableUPtr right) : BinaryOperation(std::move(left), std::move(right)) {}

        auto calculate() const -> double override { return m_left->calculate() - m_right->calculate(); }
    };

    class Divide : public BinaryOperation {
     public:
        explicit Divide(ICalculatableUPtr left, ICalculatableUPtr right) : BinaryOperation(std::move(left), std::move(right)) {}

        auto calculate() const -> double override { return m_left->calculate() / m_right->calculate(); }
    };

    class Product : public BinaryOperation {
     public:
        explicit Product(ICalculatableUPtr left, ICalculatableUPtr right) : BinaryOperation(std::move(left), std::move(right)) {}

        auto calculate() const -> double override { return m_left->calculate() * m_right->calculate(); }
    };

    class Exponentiate : public BinaryOperation {
     public:
        explicit Exponentiate(ICalculatableUPtr left, ICalculatableUPtr right) : BinaryOperation(std::move(left), std::move(right)) {}

        auto calculate() const -> double override { return std::pow(m_left->calculate(), m_right->calculate()); }
    };

}  // namespace Nummy
