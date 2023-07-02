#pragma once

#include <memory>

namespace Nummy {

    /*!
        \brief The base class of all calculatable objects

        This class represents any mathematical object that can be calculated. It can be operation, number, variable, function, etc
    */
    class ICalculatable {
     public:
        virtual auto calculate() const -> double = 0;
        virtual ~ICalculatable() {}
    };

    using ICalculatableUPtr = std::unique_ptr<ICalculatable>;

}  // namespace Nummy
