#pragma once

#include "CalculatorInitializer.hpp"

namespace Nummy {

    /*!
        \brief The base class of the programm

        Example
        \code
        #include "Application.hpp"

        int main(int argc, char** argv) {
            Nummy::Application app;
            app.run(argc, argv, std::cout);
            return 0;
        }
        \endcode
    */
    class Application {
     public:
        /*!
       Runs the program with comand line arguments
       \param[in] argc Number of arguments
       \param[in] argv Arguments
       \param[in] out Debug output stream
        */
        auto run(int argc, char** argv, std::ostream& out) -> void;

     private:
        CalculatorInitializer m_calculatorInitializer;
    };

}  // namespace Nummy
