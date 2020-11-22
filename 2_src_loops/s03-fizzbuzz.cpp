#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }

    auto const n = std::stoi(argv[1]);

    for (auto i = 1; i <= n; i++) {
        std::cout << i << " ";
        if (i % 3 == 0) {
            std::cout << "Fizz";
        }
        if (i % 5 == 0) {
            std::cout << "Buzz";
        }
        std::cout << "\n";
    }
    return 0;
}
