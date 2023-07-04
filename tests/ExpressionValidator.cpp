#include "ExpressionValidator.hpp"
#include "MathDictionary.hpp"
#include "Token.hpp"

#include <gtest/gtest.h>

namespace Nummy {

    class ExpressionValidatorTest : public testing::Test {
     protected:
        void SetUp() override {
            validTokenList = reservedTokens;

            validTokenList.emplace_back("func_name", TokenType::UnaryOperation);
            validTokenList.emplace_back("func_name2", TokenType::UnaryOperation);
        }
        void TearDown() override {}

        ExpressionValidator validator;

        std::vector<Token> validTokenList;
    };

    TEST_F(ExpressionValidatorTest, EmptyExpressionTest) {
        std::string expression("");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, CorrectAddTwoNumbersCase) {
        std::string expression("1+1");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    // TEST_F(ExpressionValidatorTest, MissingSecondArgumentCase) {
    //     std::string expression("1+");
    //     bool actual = validator.isValid(expression, validTokenList);
    //     EXPECT_FALSE(actual);
    // }

    TEST_F(ExpressionValidatorTest, ExpressionWithSpacesCase) {
        std::string expression("   1  +  1   ");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, BinaryOperationsCase) {
        std::string expression("100+200*34-12/2");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, NumbersWithFloatingPointCase) {
        std::string expression("1.00+2.999");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, IncorrectFloatingPointCase) {
        std::string expression("1.0.0");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, CorrectBracketsCase) {
        std::string expression("(1+(1-1))");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, IncorrectBracketsWithEmptyInnerCase) {
        std::string expression("(())");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, IncorrectBracketsWithMissingBracketCase) {
        std::string expression("((1)");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, NonExistingTokenCase) {
        std::string expression("1+some_name");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, AssigningCorrectVariableCase) {
        std::string expression("x=3");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, DoubleAssigningCorrectVariablesCase) {
        std::string expression("x=y=3");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_TRUE(actual);
    }

    TEST_F(ExpressionValidatorTest, AssigningIncorrectVariableNameCase) {
        std::string expression("1=3");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, AssigningReservedNameCase) {
        std::string expression("+=3");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    TEST_F(ExpressionValidatorTest, AssigningDotCase) {
        std::string expression(".=3");
        bool actual = validator.isValid(expression, validTokenList);
        EXPECT_FALSE(actual);
    }

    // TEST_F(ExpressionValidatorTest, FunctionsWithMsssingBracketsCase) {
    //     std::string expression("1+func_name345");
    //     bool actual = validator.isValid(expression, validTokenList);
    //     EXPECT_FALSE(actual);
    // }

}  // namespace Nummy
