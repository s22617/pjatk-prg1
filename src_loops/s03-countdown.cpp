#include <cstdlib>
#include <iostream>
#include <string>
auto main(int argc, char* argv[]) -> int
{
    if (argc == 0) {
        return 1;
    }
    auto const number = std::stoi(argv[1]);
    for (int i = number; i >= 0; i--) {
        std::cout << i << "..." << std::endl;
    }
    return 0;
}
