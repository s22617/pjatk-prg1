#include <iostream>
#include <string>
#include <thread>


auto print_text(std::string x) -> void
{
    std::cout << (x + "\n");
}

auto main() -> int
{
    for (auto i = 0; i < 7; i++) {
        auto s  = std::to_string(i) + "!";
        auto t1 = std::thread{print_text, std::move("Hello, t1 " + s)};
        auto t2 = std::thread{print_text, std::move("Hello, t2 " + s)};
        auto t3 = std::thread{print_text, std::move("Hello, t3 " + s)};
        auto t4 = std::thread{print_text, std::move("Hello, t4 " + s)};
        auto t5 = std::thread{print_text, std::move("Hello, t5 " + s)};
        auto t6 = std::thread{print_text, std::move("Hello, t6 " + s)};
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
    }
    return 0;
}
