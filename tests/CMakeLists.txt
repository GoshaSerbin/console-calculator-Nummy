add_executable(
    tests
    BasicCalculator.cpp
    ExpressionTokenizer.cpp
    ExpressionValidator.cpp
    CalculatableTree.cpp
    ${PROJECT_SOURCE_DIR}/src/Calculatable/CalculatableMaker.cpp
    ${PROJECT_SOURCE_DIR}/src/Calculatable/CalculatableTree.cpp
    ${PROJECT_SOURCE_DIR}/src/Core/Application.cpp
    ${PROJECT_SOURCE_DIR}/src/Core/BasicCalculator.cpp
    ${PROJECT_SOURCE_DIR}/src/Core/CalculatorInitializer.cpp
    ${PROJECT_SOURCE_DIR}/src/ExpressionProcessing/ExpressionTokenizer.cpp
    ${PROJECT_SOURCE_DIR}/src/ExpressionProcessing/ExpressionValidator.cpp
    ${PROJECT_SOURCE_DIR}/src/Math/TokensManager.cpp
    ${PROJECT_SOURCE_DIR}/src/Math/VariablesManager.cpp
)

target_link_libraries(
    tests
    gmock
    GTest::gtest_main
)

add_test(tests tests)
