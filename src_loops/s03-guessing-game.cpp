#include <iostream>
#include <random>
#include <sstream>
auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    auto const x = d100(rd);
    auto input = std::string{};
    auto y = int{};
    while (true) {
        std::cout << "guess: ";
        while (std::getline(std::cin, input)) {
            std::stringstream ss(input);
            if (ss >> y) {
                if (ss.eof()) {
                    break;
                }
            }
            std::cout << "input was not an integer!\nguess: ";
        }

        if (y < x) {
            std::cout << "number too small!" << std::endl;
        } else if (y > x) {
            std::cout << "number too big!" << std::endl;
        } else {
            std::cout << "just right!" << std::endl;
            break;
        }
    }

    return 0;
}
