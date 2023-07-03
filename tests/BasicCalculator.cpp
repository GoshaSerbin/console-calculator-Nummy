#include "BasicCalculator.hpp"

#include <gtest/gtest.h>
#include "sstream"

namespace Nummy {

    class BasicCalculatorTest : public testing::Test {
     protected:
        void SetUp() override {
            // calculator = std::make_unique<BasicCalculator>(in, out, std::move(validator), std::move(tokenizer), std::move(tree),
            //                                                std::move(tokensManager), std::move(variablesManager));
        }
        void TearDown() override {}

        std::stringstream in;
        std::stringstream out;

        std::unique_ptr<ICalculator> calculator;
    };

}  // namespace Nummy
