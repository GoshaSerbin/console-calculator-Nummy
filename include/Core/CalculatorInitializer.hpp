#pragma once

#include <iostream>
#include <memory>

namespace Nummy {

    class ICalculator;

    class CalculatorInitializer {
     public:
        /// \return empty pointer if unable to make calculator
        auto makeCalculator(int argc, char** argv, std::ostream& out) -> std::unique_ptr<ICalculator>;
    };

}  // namespace Nummy
