#pragma once

#include "IFormatter.hpp"

namespace Nummy {

    class Formatter : public IFormatter {
     public:
        auto formate(std::string message, MessageType type) -> std::string override;
    };
}  // namespace Nummy
