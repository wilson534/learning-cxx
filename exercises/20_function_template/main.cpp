#include "../exercise.h"
#include <iostream>
#include <cmath> // 引入 cmath 以使用 std::abs

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化

// 将 plus 函数模板化，使其可以处理不同的数据类型
template <typename T>
T plus(T a, T b) {
    return a + b;
}

// 为浮点数比较定义一个辅助函数，比较两个浮点数是否在一定的容忍范围内
bool almost_equal(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

int main(int argc, char **argv) {
    // 使用模板函数 plus 进行不同类型的加法操作
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");
    
    // 对于浮点数，由于精度问题，直接比较可能失败
    // 使用 almost_equal 函数进行比较
    ASSERT(almost_equal(plus(1.25f, 2.5f), 3.75f), "Plus two float");
    ASSERT(almost_equal(plus(1.25, 2.5), 3.75), "Plus two double");
    
    // TODO: 修改判断条件使测试通过
    // 原来的断言是：ASSERT(plus(0.1, 0.2) == 0.3, "How to make this pass?");
    // 修改为使用 almost_equal 进行比较
    ASSERT(almost_equal(plus(0.1, 0.2), 0.3), "How to make this pass?");
    
    return 0;
}
