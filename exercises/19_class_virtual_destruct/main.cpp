#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a; // 声明静态成员变量

    A() {
        ++num_a;
    }
    
    virtual ~A() { // 添加虚析构函数
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 在类外部初始化静态成员变量
int A::num_a = 0;

struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b; // 声明静态成员变量

    B() {
        ++num_b;
    }
    
    ~B() override { // 标记为 override（可选）
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

// 在类外部初始化静态成员变量
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A; // 创建一个 A 对象，num_a = 1
    auto b = new B; // 创建一个 B 对象，num_a = 2，num_b = 1

    // TODO: 替换 '?' 为正确的预期值
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a"); // a 和 b 都继承自 A，因此 num_a = 2
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b"); // 只有 b 是 B 对象，因此 num_b = 1
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()"); // a 是 A 对象，返回 'A'
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()"); // b 是 B 对象，返回 'B'

    delete a; // 删除 a，num_a 从 2 减少到 1
    delete b; // 删除 b，num_a 从 1 减少到 0，num_b 从 1 减少到 0
    ASSERT(A::num_a == 0, "Every A was destroyed"); // 确认所有 A 对象已被销毁
    ASSERT(B::num_b == 0, "Every B was destroyed"); // 确认所有 B 对象已被销毁

    A *ab = new B; // 创建一个指向 B 的 A 指针，num_a = 1，num_b = 1
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a"); // 只有 ab 指向一个 A 的派生类对象，因此 num_a = 1
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b"); // 只有一个 B 对象，因此 num_b = 1
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()"); // ab 指向 B 对象，返回 'B'（虚函数多态）

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    B &bb = static_cast<B&>(*ab); // 使用 static_cast 将 A& 转换为 B&
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()"); // bb 是 B 对象，返回 'B'

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab; // 由于 A 有虚析构函数，正确调用 B 的析构函数，num_a = 0，num_b = 0
    ASSERT(A::num_a == 0, "Every A was destroyed"); // 确认所有 A 对象已被销毁
    ASSERT(B::num_b == 0, "Every B was destroyed"); // 确认所有 B 对象已被销毁

    return 0;
}
