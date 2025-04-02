#include <iostream>
#include "core/game_instance.h"

int main()
{
    core::GameInstance gameInstance;

    try
    {
        gameInstance.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}