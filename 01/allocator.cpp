#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include <ctime>

class Allocator
{
private:
    char* mem_begin = nullptr;
    size_t offset = 0;
    size_t total_size = 0;

public:
    Allocator() = default;

    void makeAllocator(size_t maxSize)
    {
        if (mem_begin != nullptr) {
            delete[] mem_begin;
            offset = 0;
            total_size = 0;
            mem_begin = nullptr;
        }
        mem_begin = new char[maxSize];
        total_size = maxSize;
    }

    char* alloc(size_t size)
    {
        if (size > total_size - offset) {
            return nullptr;
        }
        offset += size;
        return mem_begin + (offset - size);
    }

    void reset()
    {
        offset = 0;
    }

    ~Allocator()
    {
        delete[] mem_begin;
    }
};

void test1()
{
    std::cout << "Test1" << std::endl;
    std::cout << "Make allocator with 20 bytes." << std::endl;
    Allocator al{};
    al.makeAllocator(20);
    std::cout << "Try allocate 21 bytes." << std::endl;
    char* res = al.alloc(21);
    assert(res == nullptr);
    std::cout << "Returned nullptr" << std::endl;
}

void test2()
{
    std::cout << "Test2" << std::endl;
    std::cout << "Make allocator with 20 bytes." << std::endl;
    Allocator al{};
    al.makeAllocator(20);
    std::cout << "Try allocate 10 bytes." << std::endl;
    char* res1 = al.alloc(10);
    assert(res1 != nullptr);
    std::cout << "Returned some pointer" << std::endl;
    std::cout << "Try allocate 5 bytes." << std::endl;
    char* res2 = al.alloc(5);
    assert(res2 != nullptr);
    std::cout << "Returned some pointer" << std::endl;
}

void test3()
{
    std::cout << "Test3" << std::endl;
    std::cout << "Make allocator with 20 bytes." << std::endl;
    Allocator al{};
    al.makeAllocator(20);
    std::cout << "Try allocate 10 bytes." << std::endl;
    char* res1 = al.alloc(10);
    assert(res1 != nullptr);
    std::cout << "Returned some pointer" << std::endl;
    std::cout << "Try allocate 11 bytes." << std::endl;
    char* res2 = al.alloc(11);
    assert(res2 == nullptr);
    std::cout << "Returned nullptr" << std::endl;
}

void test4()
{
    std::cout << "Test4" << std::endl;
    std::cout << "Make allocator with 20 bytes." << std::endl;
    Allocator al{};
    al.makeAllocator(20);
    std::cout << "Try allocate 10 bytes." << std::endl;
    char* res1 = al.alloc(10);
    assert(res1 != nullptr);
    std::cout << "RESET" << std::endl;
    al.reset();
    std::cout << "Returned some pointer" << std::endl;
    std::cout << "Try allocate 11 bytes." << std::endl;
    char* res2 = al.alloc(11);
    assert(res2 != nullptr);
    std::cout << "Returned some pointer" << std::endl;
}

void test5()
{
    std::cout << "Test 5" << std::endl;
    std::cout << "Allocate 10^9 by my allocator. Then 10^6 times call alloc(10^3)." << std::endl;
    time_t start = clock();
    Allocator al{};
    al.makeAllocator(1000000000);
    for (int i = 0; i < 1000000; i++) {
        char* pt = al.alloc(1000);
        //Some operations to avoid compiler optimizations.
        *pt = static_cast<char>('a' + i % 26);
    }
    time_t finish = clock();
    std::cout << "Completed in " << (finish - start) / static_cast<double>(CLOCKS_PER_SEC) << " sec." << std::endl;
    std::cout << "Call 10^6 times malloc(10^3)" << std::endl;
    std::vector<char*> ptrs(1000000);
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        char* pt = static_cast<char*>(malloc(1000));
        *pt = static_cast<char>('a' + i % 26);
        ptrs[i] = pt;
    }
    finish = clock();
    std::cout << "Completed in " << (finish - start) / static_cast<double>(CLOCKS_PER_SEC) << " sec." << std::endl;
    for (char* pt : ptrs) {
        free(pt);
    }
}

void test6()
{
    std::cout << "Test 6" << std::endl;
    std::cout << "Allocate 10^9 by my allocator. Then 10^7 times call alloc(10^2)." << std::endl;
    clock_t start = clock();
    Allocator al{};
    al.makeAllocator(1000000000);
    for (int i = 0; i < 10000000; i++) {
        char* pt = al.alloc(100);
        //Some operations to avoid compiler optimizations.
        *pt = static_cast<char>('a' + i % 26);
    }
    clock_t finish = clock();
    std::cout << "Completed in " << (finish - start) / static_cast<double>(CLOCKS_PER_SEC) << " sec." << std::endl;
    std::cout << "Call 10^7 times malloc(10^2)" << std::endl;
    std::vector<char*> ptrs(1000000);
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        char* pt = static_cast<char*>(malloc(1000));
        *pt = static_cast<char>('a' + i % 26);
        ptrs[i] = pt;
    }
    finish = clock();
    std::cout << "Completed in " << (finish - start) / static_cast<double>(CLOCKS_PER_SEC) << " sec." << std::endl;
    for (char* pt : ptrs) {
        free(pt);
    }
    std::cout << "OPTIMIZATIONS??" << std::endl;
}

void test7()
{
    std::cout << "Test7" << std::endl;
    std::cout << "Allocate 1000 bytes." << std::endl;
    Allocator al{};
    al.makeAllocator(1000);
    std::cout << "Call alloc(100)" << std::endl;
    char* pt = al.alloc(100);
    *pt = 'a';
    std::cout << "Allocate another 1000 bytes." << std::endl;
    al.makeAllocator(1000);
}

int main()
{
    std::vector<std::function<void(void)>> tests = {test1, test2, test3, test4, test5, test6, test7};
    for (auto const& test : tests) {
        test();
        std::cout << std::endl;
    }
}
