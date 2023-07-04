#include "Formatter.hpp"

namespace Nummy {

    namespace {
        const std::string redColor = "\033[91m";
        const std::string greenColor = "\033[92m";
        const std::string blueColor = "\033[36m";
        const std::string whiteColor = "\033[39m";
        const std::string yellowColor = "\033[33m";
        const std::string purpleColor = "\033[95m";
    }  // namespace

    auto Formatter::formate(std::string message, MessageType type) -> std::string {
        switch (type) {
            case MessageType::Error:
                message = redColor + "Error: " + whiteColor + message;
                break;
            case MessageType::Success:
                message = greenColor + message + whiteColor;
                break;
            case MessageType::Warning:
                message = greenColor + "Warning: " + whiteColor + message;
                break;
            case MessageType::Special:
                message = purpleColor + message + whiteColor;
                break;
            case MessageType::Additional:
                message = blueColor + message + whiteColor;
                break;

            default:
                break;
        }
        return message;
    }

}  // namespace Nummy
