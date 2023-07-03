#include "ExpressionTokenizer.hpp"
#include "MathDictionary.hpp"
#include "Token.hpp"

#include <gtest/gtest.h>

namespace Nummy {

    class ExpressionTokenizerTest : public testing::Test {
     protected:
        void SetUp() override {
            validTokenList = reservedTokens;

            validTokenList.emplace_back("func_name", TokenType::UnaryOperation);
            validTokenList.emplace_back("func_name2", TokenType::UnaryOperation);
            validTokenList.emplace_back("x", TokenType::Variable);
            validTokenList.emplace_back("y", TokenType::Variable);
            validTokenList.emplace_back("xy", TokenType::Variable);
        }
        void TearDown() override {}

        ExpressionTokenizer tokenizer;

        std::vector<Token> validTokenList;
    };

    TEST_F(ExpressionTokenizerTest, EmptyExpressionTest) {
        std::string expression("");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {};
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, AddTwoNumbersCase) {
        std::string expression("1+1");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, ExpressionWithSpacesCase) {
        std::string expression("   1  +  1   ");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, BinaryOperationsCase) {
        std::string expression("100+200*34-12/2");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"100", TokenType::Number         },
            {"+",   TokenType::BinaryOperation},
            {"200", TokenType::Number         },
            {"*",   TokenType::BinaryOperation},
            {"34",  TokenType::Number         },
            {"-",   TokenType::BinaryOperation},
            {"12",  TokenType::Number         },
            {"/",   TokenType::BinaryOperation},
            {"2",   TokenType::Number         }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, NumbersWithFloatingPointCase) {
        std::string expression("1.00+2.999");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"1.00",  TokenType::Number         },
            {"+",     TokenType::BinaryOperation},
            {"2.999", TokenType::Number         }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, BracketsCase) {
        std::string expression("(())");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"(", TokenType::OpenBracket },
            {"(", TokenType::OpenBracket },
            {")", TokenType::CloseBracket},
            {")", TokenType::CloseBracket}
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, UnaryMinusAndPlusCase) {
        std::string expression("+1+1+(-1)");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"+", TokenType::UnaryOperation },
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"1", TokenType::Number         },
            {"+", TokenType::BinaryOperation},
            {"(", TokenType::OpenBracket    },
            {"-", TokenType::UnaryOperation },
            {"1", TokenType::Number         },
            {")", TokenType::CloseBracket   }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, UnaryFunctionsWithSimilarNamesCase) {
        std::string expression("func_name(1)+func_name2(2)+func_name(3)");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"func_name",  TokenType::UnaryOperation },
            {"(",          TokenType::OpenBracket    },
            {"1",          TokenType::Number         },
            {")",          TokenType::CloseBracket   },
            {"+",          TokenType::BinaryOperation},
            {"func_name2", TokenType::UnaryOperation },
            {"(",          TokenType::OpenBracket    },
            {"2",          TokenType::Number         },
            {")",          TokenType::CloseBracket   },
            {"+",          TokenType::BinaryOperation},
            {"func_name",  TokenType::UnaryOperation },
            {"(",          TokenType::OpenBracket    },
            {"3",          TokenType::Number         },
            {")",          TokenType::CloseBracket   }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, AddTwoVariablesCase) {
        std::string expression("x+y");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"x", TokenType::Variable       },
            {"+", TokenType::BinaryOperation},
            {"y", TokenType::Variable       }
        };
        EXPECT_EQ(actual, expected);
    }

    TEST_F(ExpressionTokenizerTest, OperationWithSimilarVariableNamesCase) {
        std::string expression("x+xy*y");
        std::vector<Token> actual = tokenizer.tokenize(expression, validTokenList);
        std::vector<Token> expected = {
            {"x",  TokenType::Variable       },
            {"+",  TokenType::BinaryOperation},
            {"xy", TokenType::Variable       },
            {"*",  TokenType::BinaryOperation},
            {"y",  TokenType::Variable       }
        };
        EXPECT_EQ(actual, expected);
    }

}  // namespace Nummy
