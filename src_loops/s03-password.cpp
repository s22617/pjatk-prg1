#include <iostream>
#include <string>

auto main() -> int
{
    std::string haslo;
    while (haslo != "student") {
        std::cout << "password: ";
        getline(std::cin, haslo);
    }
    std::cout << "ok!\n";
    return 0;
}
