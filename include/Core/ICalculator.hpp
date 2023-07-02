#pragma once

namespace Nummy {

    class ICalculator {
     public:
        virtual auto run() -> void = 0;
        virtual ~ICalculator(){};
    };

}  // namespace Nummy
