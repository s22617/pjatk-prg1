#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 0) {
        return 1;
    }

    auto const n = std::stoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            std::cout << "FizzBuzz" << std::endl;
        } else if (i % 5 == 0) {
            std::cout << "Buzz" << std::endl;
        } else if (i % 3 == 0) {
            std::cout << "Fizz" << std::endl;
        }
    }

    return 0;
}
