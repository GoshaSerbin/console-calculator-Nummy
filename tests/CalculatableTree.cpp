#include "CalculatableTree.hpp"
#include "TokensManager.hpp"
#include "VariablesManager.hpp"

#include <gmock/gmock.h>
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

    TEST_F(CalculatableTreeTest, BracketsWithUnaryMinusAndPlusCase) {
        std::vector<Token> tokens = {
            {"-", TokenType::UnaryOperation},
            {"(", TokenType::OpenBracket   },
            {"+", TokenType::UnaryOperation},
            {"2", TokenType::Number        },
            {")", TokenType::CloseBracket  },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = -2.0;
        EXPECT_NEAR(expected, actual, tolerance);
    }

    TEST_F(CalculatableTreeTest, UnaryFunctionsCase) {
        std::vector<Token> tokens = {
            {"atan", TokenType::UnaryOperation},
            {"(",    TokenType::OpenBracket   },
            {"abs",  TokenType::UnaryOperation},
            {"(",    TokenType::OpenBracket   },
            {"sqrt", TokenType::UnaryOperation},
            {"(",    TokenType::OpenBracket   },
            {"0",    TokenType::Number        },
            {")",    TokenType::CloseBracket  },
            {")",    TokenType::CloseBracket  },
            {")",    TokenType::CloseBracket  },
        };
        tree.build(tokens);
        double actual = tree.calculate();
        double expected = 0.0;
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

    class GMockVariablesManager : public IVariablesManager {
     public:
        MOCK_METHOD(void, setVariable, (const std::string& name, double value), (override));
        MOCK_METHOD(double, getVariable, (const std::string& name), (override));
    };

    class HandlingVariablesTest : public testing::Test {
     protected:
        void SetUp() override {}
        void TearDown() override {}

        GMockVariablesManager variablesManager;
        CalculatableTree tree{variablesManager};
    };

    TEST_F(HandlingVariablesTest, SettingNewVariableCase) {
        std::vector<Token> tokens = {
            {"x",   TokenType::Variable},
            {"=",   TokenType::Asign   },
            {"100", TokenType::Number  },
        };
        EXPECT_CALL(variablesManager, setVariable("x", 100));
        tree.build(tokens);
    }

    TEST_F(HandlingVariablesTest, DoubleSettingNewVariableCase) {
        std::vector<Token> tokens = {
            {"x",   TokenType::Variable},
            {"=",   TokenType::Asign   },
            {"y",   TokenType::Variable},
            {"=",   TokenType::Asign   },
            {"100", TokenType::Number  },
        };
        EXPECT_CALL(variablesManager, setVariable("x", 100));
        EXPECT_CALL(variablesManager, setVariable("y", 100));
        tree.build(tokens);
    }

    TEST_F(HandlingVariablesTest, GettingVariableCase) {
        std::vector<Token> tokens = {
            {"x",   TokenType::Variable       },
            {"+",   TokenType::BinaryOperation},
            {"100", TokenType::Number         },
        };
        EXPECT_CALL(variablesManager, getVariable("x"));
        tree.build(tokens);
    }

}  // namespace Nummy
