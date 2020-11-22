#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    auto haslo = std::string{};
    if (argc == 2) haslo = std::string{argv[1]};

    while (haslo != "student") {
        std::cout << "password: ";
        getline(std::cin, haslo);
    }
    std::cout << "ok!\n";
    return 0;
}
