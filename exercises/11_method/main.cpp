#include "../exercise.h"
#include <iostream>

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
        if (i < cached) { // 确保 i 在已缓存范围内
            return cache[i];
        }
        for (; cached <= i; ++cached) { // 确保包括 i
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体，通过构造函数自动完成
    Fibonacci fib;
    
    // 验证第 10 个斐波那契数
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
