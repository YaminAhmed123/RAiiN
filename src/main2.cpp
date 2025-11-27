#include <render_engine.hpp>
#include <iostream>

int main(){

    RenderEngine renderEngine;
    renderEngine.run();

    if(vulkanaid::DEBUG_MODE){
        std::cin.get();
    }

    return 0;
}