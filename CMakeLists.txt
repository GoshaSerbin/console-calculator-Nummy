cmake_minimum_required(VERSION 3.0.0)
project(Nummy VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/Calculatable/CalculatableMaker.cpp
    src/Calculatable/CalculatableTree.cpp
    src/Core/Application.cpp
    src/Core/BasicCalculator.cpp
    src/Core/CalculatorInitializer.cpp
    src/ExpressionProcessing/ExpressionTokenizer.cpp
    src/ExpressionProcessing/ExpressionValidator.cpp
    src/Math/TokensManager.cpp
    src/Math/VariablesManager.cpp
    src/main.cpp)

set(INCLUDES
    include/Calculatable
    include/Core
    include/ExpressionProcessing
    include/Math)

include_directories(${INCLUDES} ${PROJECT_BINARY_DIR})

configure_file(ProjectParameters.hpp.in ProjectParameters.hpp)

option(ENABLE_TESTS "Enable tests" TRUE)

if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_compile_options(--coverage)
    add_link_options(--coverage)

    add_subdirectory(tests)

    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
