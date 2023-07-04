#pragma once

#include <string>

namespace Nummy {

    /*!
    \brief class is responsable for working with variables


    */
    class IVariablesManager {
     public:
        virtual auto setVariable(const std::string& name, double value) -> void = 0;
        virtual auto getVariable(const std::string& name) -> double = 0;
        virtual ~IVariablesManager() {}
    };

}  // namespace Nummy
