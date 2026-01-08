#include "../include/Game.h"
#include <iostream>
#include <exception>

int main(int argc, char* argv[]) {
    try {
        Zork::Game game;
        game.start();
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
