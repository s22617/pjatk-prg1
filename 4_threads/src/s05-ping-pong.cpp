#include <algorithm>
#include <array>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto print(std::queue<int>& q,
           std::mutex& mtx,
           std::condition_variable& cv,
           std::array<std::string, 2>& array,
           std::string const call) -> void
{
    std::random_device rd;
    std::uniform_int_distribution<int> d42(1, 42);

    while (true) {
        std::unique_lock<std::mutex> lck{mtx};
        cv.wait(lck);
        if (array[0] == call) {
            auto number = q.front();
            q.pop();

            std::cout << call << " " << number << std::endl;
            number += d42(rd);
            q.push(number);

            std::swap(array[0], array[1]);
            cv.notify_one();

            if (number > 1024) {
                break;
            }
        } else {
            lck.unlock();
            cv.notify_one();
        }
    }
}

auto main() -> int
{
    auto queue = std::queue<int>{};
    queue.push(0);
    std::mutex mtx;
    std::condition_variable cv;
    std::array<std::string, 2> array = {"Ping", "Pong"};


    auto ping = std::thread{print,
                            std::ref(queue),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(array),
                            "Ping"};

    auto pong = std::thread{print,
                            std::ref(queue),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(array),
                            "Pong"};


    ping.join();
    pong.join();

    return 0;
}
