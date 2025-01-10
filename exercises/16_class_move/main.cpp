#include "../exercise.h"
#include <iostream>
#include <stdexcept>
#include <memory> // For std::unique_ptr
#include <utility> // For std::move

class DynFibonacci {
    std::unique_ptr<size_t[]> cache; // 使用智能指针管理动态数组
    int cached;
    int capacity;

public:
    // 构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        if (capacity < 2) {
            throw std::invalid_argument("Capacity must be at least 2.");
        }
        cache[0] = 0;
        cache[1] = 1;
        for(int j = 2; j < capacity; ++j) {
            cache[j] = 0;
        }
    }

    // 移动构造函数
    DynFibonacci(DynFibonacci &&other) noexcept : cache(std::move(other.cache)), cached(other.cached), capacity(other.capacity) {
        other.cached = 0;
        other.capacity = 0;
    }

    // 移动赋值运算符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            cache = std::move(other.cache);
            cached = other.cached;
            capacity = other.capacity;
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 禁用拷贝构造函数和拷贝赋值运算符
    DynFibonacci(const DynFibonacci&) = delete;
    DynFibonacci& operator=(const DynFibonacci&) = delete;

    // 获取斐波那契数的引用，以便赋值
    size_t& operator[](int i) {
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Fibonacci index out of range.");
        }

        if (i < cached) {
            return cache[i];
        }

        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }

        return cache[i];
    }

    // 常量版本
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // 检查对象是否仍然拥有缓存资源
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    try {
        // 初始化动态缓存容量为 12
        DynFibonacci fib(12);
        ASSERT(fib[10] == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib[10] << std::endl;

        // 尝试移动构造对象
        DynFibonacci const fib_ = std::move(fib);
        ASSERT(!fib.is_alive(), "Object moved");
        ASSERT(fib_[10] == 55, "fibonacci(10) should be 55 from cloned object");
        std::cout << "fibonacci(10) from cloned object = " << fib_[10] << std::endl;

        // 测试移动赋值运算符
        DynFibonacci fib0(6);
        DynFibonacci fib1(12);

        fib1[5] = 5; // 设定一个值，以确保赋值后 fib0 可以计算更高的数
        fib0 = std::move(fib1);
        ASSERT(!fib1.is_alive(), "fib1 moved");
        ASSERT(fib0[10] == 55, "fibonacci(10) should be 55 after move assignment");
        std::cout << "fibonacci(10) after move assignment = " << fib0[10] << std::endl;

        // 自移动赋值
        fib0 = std::move(fib0);
        ASSERT(fib0.is_alive(), "fib0 should still be alive after self-move");
        ASSERT(fib0[10] == 55, "fibonacci(10) should still be 55 after self-move");
        std::cout << "fibonacci(10) after self-move assignment = " << fib0[10] << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
