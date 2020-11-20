#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }
    auto const number = std::stoi(argv[1]);
    for (auto i = number; i > 0; i--) {
        std::cout << i << "..." << std::endl;
    }
    std::cout << "0...\n";
    return 0;
}
