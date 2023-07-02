#pragma once

#include "ICalculatable.hpp"

namespace Nummy {

    class Number : public ICalculatable {
     public:
        explicit Number(double value) : m_value(value) {}

        auto calculate() const -> double override { return m_value; }

     private:
        double m_value;
    };

}  // namespace Nummy
