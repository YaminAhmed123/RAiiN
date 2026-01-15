#include <render_engine.hpp>
#include <tools.hpp>
#include <iostream>

int main(){
    LOG("Starting HATE Render Engine...");

    RenderEngine renderEngine;
    renderEngine.run();

    if(vulkanaid::DEBUG_MODE){
        std::cin.get();
    }

    return 0;
}