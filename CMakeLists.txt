cmake_minimum_required(VERSION 3.5.0)
project(Nummy VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Werror -Wpedantic)

set(SOURCES
    src/Calculatable/CalculatableMaker.cpp
    src/Calculatable/CalculatableTree.cpp
    src/Core/Application.cpp
    src/Core/BasicCalculator.cpp
    src/Core/CalculatorInitializer.cpp
    src/Core/FormatCalculator.cpp
    src/ExpressionProcessing/ExpressionTokenizer.cpp
    src/ExpressionProcessing/ExpressionValidator.cpp
    src/Formatter/Formatter.cpp
    src/Math/TokensManager.cpp
    src/Math/VariablesManager.cpp
    src/main.cpp)

set(INCLUDES
    include/Calculatable
    include/Core
    include/ExpressionProcessing
    include/Formatter
    include/Math)

include_directories(${INCLUDES} ${PROJECT_BINARY_DIR})

configure_file(ProjectParameters.hpp.in ProjectParameters.hpp)

option(ENABLE_TESTS "Enable tests" TRUE)
option(ENABLE_COVERAGE "Enable coverage" TRUE)
option(ENABLE_SANITIZERS "Enable sanitizers" TRUE)

if(ENABLE_COVERAGE OR ENABLE_SANITIZERS OR ENABLE_TESTS)
    add_compile_options(-g -O0)
elseif()
    add_compile_options(-Ofast)
endif()

if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)
endif()

if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(tests)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
