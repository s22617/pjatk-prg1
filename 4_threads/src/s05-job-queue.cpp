#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

auto print_line(std::string ID, std::queue<int>& q, std::mutex& q_mtx) -> void
{
    while (true) {
        {
            std::unique_lock<std::mutex> lck{q_mtx};
            if (q.empty()) {
                break;
            }
            auto number = q.front();
            q.pop();
            lck.unlock();
            std::cout << "from thread " + ID + " : " + std::to_string(number) + "\n";
        }
    }
}

auto main() -> int
{
    std::queue<int> queue;
    for (auto j = 0; j < 11; j++) {
        queue.push(j);
    }

    std::mutex q_mtx;

    auto ts = std::vector<std::unique_ptr<std::thread>>{};

    for (auto i = 0; i < 4; i++) {
        auto t = std::make_unique<std::thread>(
            print_line, std::to_string(i), std::ref(queue), std::ref(q_mtx));
        ts.push_back(std::move(t));
    }

    for (auto& t : ts) {
        t->join();
    }

    return 0;
}
