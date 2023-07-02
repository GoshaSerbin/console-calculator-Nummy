#include "CalculatableMaker.hpp"
#include "BinaryOperations.hpp"
#include "MathDictionary.hpp"
#include "Number.hpp"
#include "UnaryOperations.hpp"

namespace Nummy {

    auto CalculatableMaker::makeBinaryOperation(const std::string& name, ICalculatableUPtr left, ICalculatableUPtr right)
        -> ICalculatableUPtr {
        if (name == ReservedSymbols::plus) {
            return std::make_unique<Add>(std::move(left), std::move(right));
        }
        if (name == ReservedSymbols::minus) {
            return std::make_unique<Subtract>(std::move(left), std::move(right));
        }
        if (name == ReservedSymbols::divide) {
            return std::make_unique<Divide>(std::move(left), std::move(right));
        }
        if (name == ReservedSymbols::product) {
            return std::make_unique<Product>(std::move(left), std::move(right));
        }
        if (name == ReservedSymbols::exponentiate) {
            return std::make_unique<Exponentiate>(std::move(left), std::move(right));
        }
        return {};
    }

    auto CalculatableMaker::makeUnaryOperation(const std::string& name, ICalculatableUPtr argument) -> ICalculatableUPtr {
        if (name == ReservedSymbols::plus) {
            return std::make_unique<Plus>(std::move(argument));
        }
        if (name == ReservedSymbols::minus) {
            return std::make_unique<Minus>(std::move(argument));
        }
        if (name == ReservedSymbols::abs) {
            return std::make_unique<Abs>(std::move(argument));
        }
        if (name == ReservedSymbols::sqrt) {
            return std::make_unique<Sqrt>(std::move(argument));
        }
        if (name == ReservedSymbols::atan) {
            return std::make_unique<Atan>(std::move(argument));
        }
        return {};
    }
    auto CalculatableMaker::makeNumber(double number) -> ICalculatableUPtr {
        return std::make_unique<Number>(number);
    }

}  // namespace Nummy
