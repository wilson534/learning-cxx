#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;    // 动态分配的缓存数组
    int cached;       // 当前缓存的斐波那契数的数量
    int capacity;     // 缓存容量

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

    // TODO: 实现复制构造器
    /// @brief 复制构造函数，执行深拷贝。
    /// @param other 要复制的 `DynFibonacci` 对象
    DynFibonacci(const DynFibonacci& other) : cache(new size_t[other.capacity]), cached(other.cached), capacity(other.capacity) {
        for(int j = 0; j < other.capacity; ++j) {
            cache[j] = other.cache[j];
        }
    }

    // TODO: 实现析构器，释放缓存空间
    /// @brief 析构函数，释放动态分配的缓存空间。
    ~DynFibonacci() {
        delete[] cache;
    }

    // 禁用拷贝赋值运算符，遵循三法则
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

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    try {
        DynFibonacci fib(12);
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

        // 尝试复制对象
        DynFibonacci const fib_ = fib;
        ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
        std::cout << "fibonacci(10) from cloned object = " << fib_.get(10) << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
