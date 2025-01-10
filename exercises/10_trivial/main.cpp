#include "../exercise.h"
#include <iostream>

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if (i <= cache.cached) {
        return cache.cache[i];
    }
    for (; cache.cached <= i; ++cache.cached) { // 注意这里的 <=，确保包括 i
        cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体，设置 cache[0] = 0 和 cache[1] = 1，cached = 2
    FibonacciCache fib{ {0, 1}, 2 };
    
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
