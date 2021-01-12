#include <unistd.h>

#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto print_line(std::queue<std::string>& q, std::mutex& q_mtx, int const ID)
    -> void
{
    while (true) {
        std::random_device rd;
        std::uniform_int_distribution<int> d100(10, 100);
        while (q.empty()) {
            // std::cout << "THREAD SLEEPING";
            sleep(d100(rd) / 1000);
        }
        {
            // std::cout << "THREAD MUTEX LOCKED" << std::endl;
            std::lock_guard<std::mutex> lck{q_mtx};
            auto line = q.front();
            q.pop();
            // std::cout << "Before line.empty()" << std::endl;
            if (line.empty()) {
                std::cout << "Thread " + std::to_string(ID) + " exiting\n";
                break;
            }

            std::cout << "Thread ID: " + std::to_string(ID) + " reads: " + line
                      << std::endl;
        }
    }
}

auto main() -> int
{
    auto queue = std::queue<std::string>{};
    std::mutex mtx;

    auto t1 = std::thread{print_line, std::ref(queue), std::ref(mtx), 1};
    auto t2 = std::thread{print_line, std::ref(queue), std::ref(mtx), 2};
    auto t3 = std::thread{print_line, std::ref(queue), std::ref(mtx), 3};
    auto t4 = std::thread{print_line, std::ref(queue), std::ref(mtx), 4};
    auto empty_lines = 0;

    while (true) {
        auto line = std::string{};
        std::getline(std::cin, line);
        if (line.empty()) {
            empty_lines++;
        }
        {
            // std::cout << "WHILE MUTEX LOCKED" << std::endl;
            std::lock_guard<std::mutex> lck{mtx};
            queue.push(std::move(line));
        }
        if (empty_lines >= 4) {
            break;
        }
    }

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
