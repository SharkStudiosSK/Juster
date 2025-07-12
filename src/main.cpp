#include "juster/Application.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Juster::Application& app = Juster::Application::getInstance();
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application!" << std::endl;
        return 1;
    }

    int exitCode = app.run();
    
    app.shutdown();
    
    return exitCode;
}