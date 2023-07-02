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

}  // namespace Nummy

// #include <cmath>
// #include <gtest/gtest.h>
// #include <sstream>
// #include <string>

// class ConsoleCalculatorTest : public testing::Test {
//  protected:
//     void SetUp() override {
//         argc = 2;
//         argv = new char*[argc];
//         argv[0] = const_cast<char*>("hw2");
//     }
//     void TearDown() override { delete[] argv; }
//     char** argv;
//     int argc;
//     ConsoleCalculator calculator;
// };

// TEST_F(ConsoleCalculatorTest, Add2NumbersTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+1");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "2";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, Add10NumbersTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+2+3+4+5+6+7+8+9+10");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "55";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, SubstractNumbersTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("10-10");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "0";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, SubstractAndAddNumbersTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+2-2-1");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "0";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, Divide2NumbersTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1/2");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "0.5";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, DividePriorityTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+1/2");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "1.5";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, BracketsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+2-(2+2)");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "-1";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, PriorityTestWithDivideAndBrackets) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+3/(3-1)");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "2.5";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, TestWithUnaryMinus) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("-1+1");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "0";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, AbsFunctionTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("abs(-10.5)");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "10.5";

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, AtanFunctionTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("atan(0.5)");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = std::to_string(std::atan(0.5));

//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, NoInputArgumentTest) {
//     std::stringstream ss;
//     argc = 1;
//     EXPECT_NO_THROW(calculator.run(argc, argv, ss));
// }

// TEST_F(ConsoleCalculatorTest, NotEnoughBracketsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("(1+(1+0)");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, TooMuchBracketsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("(1+(1+0)))");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, InCorrectBracketsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("(1)+1)+(1+0)");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, EmptyInputTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>(" ");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, MissingSecondArgumentTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, MissingFirstArgumentTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("+1");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, EmptyArgumentInBracketsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+()");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, EmptyArgumentInFunctionTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("atan()");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, NoArgumentInFunctionTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("abs");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }

// TEST_F(ConsoleCalculatorTest, InputWithSpacesTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1 + 2 -    3 / 1 + atan  ( 0 )");
//     calculator.run(argc, argv, ss);
//     std::string actual(ss.str());
//     std::string expected = "0";
//     EXPECT_EQ(expected, actual);
// }

// TEST_F(ConsoleCalculatorTest, UndefinedSymbolsTest) {
//     std::stringstream ss;
//     argv[1] = const_cast<char*>("1+2+3+r+4");
//     EXPECT_THROW(calculator.run(argc, argv, ss), Error);
// }