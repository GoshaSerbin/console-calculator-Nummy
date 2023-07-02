#include "Application.hpp"

int main(int argc, char** argv) {
    Nummy::Application app;
    app.run(argc, argv, std::cout);
    return 0;
}
