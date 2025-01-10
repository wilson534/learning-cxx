#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// 定义 Fibonacci 结构体
struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数，初始化 cache 和 cached
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
        // 可选：初始化其余 cache 元素为 0
        for(int j = 2; j < 128; ++j) {
            cache[j] = 0;
        }
    }

    // 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 添加边界检查
        if (i < 0 || i >= 128) {
            throw std::out_of_range("Fibonacci index out of range (0-127)");
        }

        if (i < cached) { // 确保 i 在已缓存范围内
            return cache[i];
        }
        for (; cached <= i; ++cached) { // 循环条件改为 cached <= i
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    try {
        // 初始化缓存结构体，通过构造函数自动完成
        Fibonacci fib;

        // 验证第 10 个斐波那契数
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

        // 可选：更多测试
        ASSERT(fib.get(20) == 6765, "fibonacci(20) should be 6765");
        std::cout << "fibonacci(20) = " << fib.get(20) << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
