#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;      // 动态分配的缓存数组
    int cached;         // 当前缓存的斐波那契数的数量
    int capacity;       // 缓存容量

public:
    // TODO: 实现动态设置容量的构造器
    /// @brief 构造函数，动态分配缓存空间并初始化前两个斐波那契数。
    /// @param capacity 缓存容量
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        if (capacity < 2) {
            delete[] cache;
            throw std::invalid_argument("Capacity must be at least 2.");
        }
        cache[0] = 0;
        cache[1] = 1;
        // 可选：初始化其余 cache 元素为 0（避免未初始化）
        for(int j = 2; j < capacity; ++j) {
            cache[j] = 0;
        }
    }

    // TODO: 实现析构器，释放缓存空间
    /// @brief 析构函数，释放动态分配的缓存空间。
    ~DynFibonacci() {
        delete[] cache;
    }

    // 禁用拷贝构造函数和拷贝赋值运算符，遵循三法则
    DynFibonacci(const DynFibonacci&) = delete;
    DynFibonacci& operator=(const DynFibonacci&) = delete;

    // TODO: 实现正确的缓存优化斐波那契计算
    /// @brief 获取第 i 个斐波那契数。
    /// @param i 斐波那契数的索引（从 0 开始）
    /// @return 第 i 个斐波那契数
    size_t get(int i) {
        // 添加边界检查，防止数组越界
        if (i < 0 || i >= capacity) {
            throw std::out_of_range("Fibonacci index out of range.");
        }

        if (i < cached) { // 确保 i 在已缓存范围内
            return cache[i];
        }

        // 计算并缓存新的斐波那契数，直到缓存到第 i 个
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }

        return cache[i];
    }
};

int main(int argc, char **argv) {
    try {
        // 初始化动态缓存容量为 20
        DynFibonacci fib(20);

        // 验证第 10 个斐波那契数
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

        // 验证第 15 个斐波那契数
        ASSERT(fib.get(15) == 610, "fibonacci(15) should be 610");
        std::cout << "fibonacci(15) = " << fib.get(15) << std::endl;

        // 可选：更多测试
        // ASSERT(fib.get(19) == 4181, "fibonacci(19) should be 4181");
        // std::cout << "fibonacci(19) = " << fib.get(19) << std::endl;

        // 测试边界条件
        // ASSERT(fib.get(20) == ?, "fibonacci(20) should be ..."); // 应抛出异常
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
