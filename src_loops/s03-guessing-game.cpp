#include <iostream>
#include <random>
auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    auto const x = d100(rd);
    int y;
    while (true) {
        std::cout << "guess: ";
        std::cin >> y;
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
