#pragma once

#include "IFormatter.hpp"

namespace Nummy {

    class Formatter : public IFormatter {
     public:
        auto formate(const std::string& message, MessageType type) -> std::string override;

     private:
    };
}  // namespace Nummy
