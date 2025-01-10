#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// C++ 中，`class` 和 `struct` 之间的**唯一区别**是
// `class` 默认访问控制符是 `private`，
// `struct` 默认访问控制符是 `public`。
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

// 这个 class 中的字段被 private 修饰，只能在 class 内部访问。
// 因此必须提供构造器来初始化字段。
// READ: 构造器 <https://zh.cppreference.com/w/cpp/language/constructor>
class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造器
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
        // 初始化其余 cache 元素为 0（可选）
        for(int j = 2; j < 16; ++j) {
            cache[j] = 0;
        }
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 添加边界检查，防止数组越界
        if (i < 0 || i >= 16) {
            throw std::out_of_range("Fibonacci index out of range (0-15)");
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
        // 现在类型拥有无参构造器，声明时会直接调用。
        // 这个写法不再是未定义行为了。
        Fibonacci fib;

        // 验证第 10 个斐波那契数
        ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
        std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

        // 可选：更多测试
        ASSERT(fib.get(15) == 610, "fibonacci(15) should be 610");
        std::cout << "fibonacci(15) = " << fib.get(15) << std::endl;

        // 如果需要，可以添加更多测试
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
