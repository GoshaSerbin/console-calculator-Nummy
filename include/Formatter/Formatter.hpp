#pragma once

#include "IFormatter.hpp"

namespace Nummy {

    /*!
    Formats messages.

    Adds colors and prefixes depending on MessageType
    */
    class Formatter : public IFormatter {
     public:
        auto formate(std::string message, MessageType type) -> std::string override;
    };

}  // namespace Nummy
