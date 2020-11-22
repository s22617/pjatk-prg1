#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }

    auto const parameter = std::string{argv[1]};

    if (parameter == "-r") {
        int r = argc - 1;
        if (argc > 1 && std::string{argv[2]} == "-l") {
            while (r > 0) {
                std::cout << std::string{argv[r]} << std::endl;
                --r;
            }
        } else if (argc > 1 && std::string{argv[2]} == "-n") {
            while (r > 0) {
                std::cout << std::string{argv[r]} << " ";
                --r;
            }

        } else {
            int r = argc - 1;
            while (r > 0) {
                std::cout << std::string{argv[r]} << " ";
                --r;
            }
        }
        std::cout << std::endl;
    } else if (parameter == "-n") {
        for (int i = 1; i < argc; i++) {
            std::cout << std::string{argv[i]} << " ";
        }
    } else if (parameter == "-l") {
        for (int i = 1; i < argc; i++) {
            std::cout << std::string{argv[i]} << std::endl;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            std::cout << std::string{argv[i]} << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
