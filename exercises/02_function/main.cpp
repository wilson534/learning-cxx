#include "../exercise.h"

// 声明 add 函数
int add(int a, int b);

int main(int argc, char **argv) {
    ASSERT(add(123, 456) == 123 + 456, "add(123, 456) should be 123 + 456");

    auto x = 1, y = 2;
    std::cout << x << " + " << y << " = " << add(x, y) << std::endl;
    return 0;
}

// 补全 add 函数的定义
int add(int a, int b) {
    return a + b;
}
