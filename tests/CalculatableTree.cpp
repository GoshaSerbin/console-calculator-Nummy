#include "CalculatableTree.hpp"
#include "TokensManager.hpp"
#include "VariablesManager.hpp"

#include <gtest/gtest.h>

namespace Nummy {

    namespace {
        const double tolerance = 1e-13;
    }

    class CalculatableTreeTest : public testing::Test {
     protected:
        void SetUp() override {}
        void TearDown() override {}

        TokensManager tokensManager;
        VariablesManager variablesManager{tokensManager};
        CalculatableTree tree{variablesManager};
    };

    TEST_F(CalculatableTreeTest, AddTwoNumbersCase) {
        std::vector<Token> tokens = {
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 2.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

    TEST_F(CalculatableTreeTest, OperationPriorityCase) {
        std::vector<Token> tokens = {
            {"2", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"2", TokenType::Number         },
            {"*", TokenType::BinaryOperation},
            {"2", TokenType::Number         },
            {"^", TokenType::BinaryOperation},
            {"3", TokenType::Number         },
            {"/", TokenType::BinaryOperation},
            {"2", TokenType::Number         },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 10.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

    TEST_F(CalculatableTreeTest, BracketsWithUnaryMinusCase) {
        std::vector<Token> tokens = {
            {"-", TokenType::UnaryOperation},
            {"(", TokenType::OpenBracket   },
            {"-", TokenType::UnaryOperation},
            {"2", TokenType::Number        },
            {")", TokenType::CloseBracket  },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 2.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

    TEST_F(CalculatableTreeTest, NestedBracketsCase) {
        std::vector<Token> tokens = {
            {"(", TokenType::OpenBracket    },
            {"(", TokenType::OpenBracket    },
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         },
            {")", TokenType::CloseBracket   },
            {"-", TokenType::BinaryOperation},
            {"(", TokenType::OpenBracket    },
            {"(", TokenType::OpenBracket    },
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         },
            {")", TokenType::CloseBracket   },
            {")", TokenType::CloseBracket   },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 0.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

    TEST_F(CalculatableTreeTest, SeveralLevelsOfRecursiveCase) {
        std::vector<Token> tokens = {
            {"4", TokenType::Number         },
            {"*", TokenType::BinaryOperation},
            {"(", TokenType::OpenBracket    },
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"3", TokenType::Number         },
            {")", TokenType::CloseBracket   },
            {"^", TokenType::BinaryOperation},
            {"2", TokenType::Number         },
            {"-", TokenType::BinaryOperation},
            {"1", TokenType::Number         },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 63.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

}  // namespace Nummy
