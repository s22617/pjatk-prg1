#include <itp/channel.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>

auto print_line(itp::channel<std::string>& ch, int const ID) -> void
{
    std::string line = ch.wait();

    while (not line.empty()) {
        std::cout << "Thread " + std::to_string(ID) + " reads: " + line
                  << std::endl;
        try {
            line = ch.wait();
        } catch (itp::timeout_expired_error const&) {
        }
    }
    std::cout << "Thread " + std::to_string(ID) + ": exiting" << std::endl;
}

auto main() -> int
{
    auto ch = itp::channel<std::string>{};
    auto t1 = std::thread{print_line, std::ref(ch), 1};
    auto t2 = std::thread{print_line, std::ref(ch), 2};
    auto t3 = std::thread{print_line, std::ref(ch), 3};
    auto t4 = std::thread{print_line, std::ref(ch), 4};

    auto empty_lines = 0;

    {
        auto line = std::string{};
        do {
            std::getline(std::cin, line);
            ch.push(line);
            if (line.empty()) {
                empty_lines++;
            }
        } while (empty_lines < 4);
    }

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
