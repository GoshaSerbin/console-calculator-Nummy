#include "Application.hpp"
#include "ICalculator.hpp"

#include <iostream>

namespace Nummy {

    auto Application::run(int argc, char** argv, std::ostream& out = std::cout) -> void {
        auto calculator = m_calculatorInitializer.makeCalculator(argc, argv, out);
        if (calculator) {
            calculator->run();
        }
    }

}  // namespace Nummy
