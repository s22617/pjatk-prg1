#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


auto print_line(std::queue<std::string>& q,
                std::mutex& q_mtx,
                std::condition_variable& cv,
                int const ID) -> void
{
    while (true) {
        std::unique_lock<std::mutex> lck{q_mtx};
        cv.wait(lck);

        auto line = q.front();
        q.pop();
        lck.unlock();
        if (line.empty()) {
            std::cout << "Thread " + std::to_string(ID) + ": exiting\n";
            break;
        }
        std::cout << "Thread " + std::to_string(ID) + " reads: " + line + "\n";
    }
}

auto main() -> int
{
    auto queue = std::queue<std::string>{};
    std::mutex mtx;
    std::condition_variable cv;

    auto t1 = std::thread{
        print_line, std::ref(queue), std::ref(mtx), std::ref(cv), 1};
    auto t2 = std::thread{
        print_line, std::ref(queue), std::ref(mtx), std::ref(cv), 2};
    auto t3 = std::thread{
        print_line, std::ref(queue), std::ref(mtx), std::ref(cv), 3};
    auto t4 = std::thread{
        print_line, std::ref(queue), std::ref(mtx), std::ref(cv), 4};

    auto empty_lines = 0;

    while (true) {
        auto line = std::string{};
        std::getline(std::cin, line);
        if (line.empty()) {
            empty_lines++;
        }
        {
            std::unique_lock<std::mutex> lck{mtx};
            queue.push(std::move(line));
        }
        cv.notify_one();

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
