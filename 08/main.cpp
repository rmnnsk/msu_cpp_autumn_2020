#include <iostream>
#include <functional>
#include <cassert>
#include "thread_pool.h"

void test1()
{
    std::cout << "TEST 1" << std::endl;
    std::cout << "Test basic functionality" << std::endl;
    std::cout << "Task number(5) less than pool size(10) " << std::endl;
    ThreadPool pool(10);
    std::vector<std::future<int>> task_futures;
    std::cout << "Put in thread pool 5 functions and check return values." << std::endl;
    for (int i = 0; i < 5; i++) {
        auto fut = pool.exec([i]() {
            return i;
        });
        task_futures.push_back(std::move(fut));
    }
    for (int i = 0; i < 5; i++) {
        auto t = task_futures[i].get();
        assert(t == i);
    }
    std::cout << "Task number(15) more than pool size(10) " << std::endl;
    std::cout << "Put in thread pool 15 functions and check return values." << std::endl;
    std::vector<std::future<int>> task_futures_2;
    for (int i = 0; i < 15; i++) {
        auto fut = pool.exec([i]() {
            return i;
        });
        task_futures_2.push_back(std::move(fut));
    }
    for (int i = 0; i < 15; i++) {
        auto t = task_futures_2[i].get();
        assert(t == i);
    }
}

void test2()
{
    std::cout << "TEST 2" << std::endl;
    std::cout << "Test early pool destruction." << std::endl;
    std::vector<std::future<int>> task_futures;
    {
        std::cout << "Create scope with ThreadPool(2) and put there 20 tasks." << std::endl;
        ThreadPool pool(2);
        for (int i = 0; i < 20; i++) {
            auto fut = pool.exec([i]() {
                return i;
            });
            task_futures.push_back(std::move(fut));
        }
        std::cout << "Exit from scope and destruct pool." << std::endl;
    }
    std::cout << "Check for pool doesn't brake any promise." << std::endl;
    for (int i = 0; i < 20; i++) {
        auto t = task_futures[i].get();
        assert(t == i);
    }
}

void test3()
{
    std::cout << "TEST 3" << std::endl;
    std::cout << "Test different function return value." << std::endl;
    ThreadPool pool(4);
    auto str_fut = pool.exec([]() {
        return "prekol";
    });
    auto str = str_fut.get();
    std::string test_str = "prekol";
    assert(str == test_str);

}

int main()
{
    std::vector<std::function<void()>> tests = {test1, test2, test3};
    for (const auto &test: tests) {
        test();
        std::cout << "------------------------------------------------------------------" << std::endl;
    }
}
