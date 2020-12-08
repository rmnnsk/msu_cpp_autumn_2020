#pragma once

#include <future>
#include <functional>
#include <vector>
#include <queue>

class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize = std::thread::hardware_concurrency()) : poolSize(poolSize)
    {
        for (size_t i = 0; i < poolSize; i++) {
            pool.emplace_back(std::thread([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(mutex);
                    queue_ready.wait(lock, [&]() {
                        return !tasks_queue.empty() || terminate;
                    });
                    if (terminate && tasks_queue.empty()) {
                        break;
                    }
                    auto task = std::move(tasks_queue.front());
                    tasks_queue.pop();
                    lock.unlock();
                    task();
                }
            }));
        }
    }

    // pass arguments by value
    template<class Func, class... Args>
    auto exec(Func func, Args ...args) -> std::future<decltype(func(args...))>
    {
        using R = decltype(func(args...));
        auto task = std::packaged_task<R()>(std::bind(func, args...));
        auto task_future = task.get_future();
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks_queue.emplace(std::move(task));
        }
        queue_ready.notify_one();
        return task_future;
    }

    ~ThreadPool()
    {
        terminate = true;
        queue_ready.notify_all();
        for (auto &thr: pool) {
            thr.join();
        }
    }

private:
    size_t poolSize;
    std::vector<std::thread> pool;
    std::queue<std::packaged_task<void()>> tasks_queue;
    std::mutex mutex;
    std::condition_variable queue_ready;
    bool terminate = false;
};