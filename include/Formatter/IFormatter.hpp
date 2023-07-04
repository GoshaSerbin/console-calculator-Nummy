#pragma once

#include <string>

namespace Nummy {

    enum class MessageType {
        Default,
        Error,
        Success,
        Warning,
        Special,
    };

    class IFormatter {
     public:
        virtual auto formate(const std::string& message, MessageType type) -> std::string = 0;
        virtual ~IFormatter() {}
    };

}  // namespace Nummy
