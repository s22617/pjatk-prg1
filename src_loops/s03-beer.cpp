#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    int i = 99;
    if (argc > 1) {
        i = std::stoi(argv[1]);
    }
    do {
        std::cout << i << " bottles of beer on the wall, " << i
                  << " bottles of beer." << std::endl;
        i--;
        std::cout << "Take one down, pass it around, ";
    } while (i > 0);
    std::cout << "No more bottles of beer on the wall, no more bottles of beer."
              << std::endl;
    std::cout << "Go to the store and buy some more, 99 bottles of beer on the "
                 "wall..."
              << std::endl;

    return 0;
}
