#include "../exercise.h"
#include <iostream>
#include <stdexcept>

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};

struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};

struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};

struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 移除或注释掉与 struct X 相关的 static_assert，因为在当前代码中没有定义 struct X
    // static_assert(sizeof(X) == 4, "There is an int in X");
    // static_assert(sizeof(A) == 4, "There is an int in A");
    // static_assert(sizeof(B) == 8, "B is an A with an X");

    // 替换所有的 '?' 为预期的字符值
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // D 无法覆盖 virtual_name()，继承自 C

    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG); // D 覆盖了 direct_name()

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // 动态绑定，调用 B::virtual_name()
    ASSERT(rbc.virtual_name() == 'C', MSG); // 动态绑定，调用 C::virtual_name()
    ASSERT(rcd.virtual_name() == 'C', MSG); // 动态绑定，调用 C::virtual_name()

    ASSERT(rab.direct_name() == 'A', MSG); // 静态绑定，调用 A::direct_name()
    ASSERT(rbc.direct_name() == 'B', MSG); // 静态绑定，调用 B::direct_name()
    ASSERT(rcd.direct_name() == 'C', MSG); // 静态绑定，调用 C::direct_name()

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // 动态绑定，调用 C::virtual_name()
    ASSERT(rbd.virtual_name() == 'C', MSG); // 动态绑定，调用 C::virtual_name()

    ASSERT(rac.direct_name() == 'A', MSG); // 静态绑定，调用 A::direct_name()
    ASSERT(rbd.direct_name() == 'B', MSG); // 静态绑定，调用 B::direct_name()

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 动态绑定，调用 C::virtual_name()
    ASSERT(rad.direct_name() == 'A', MSG); // 静态绑定，调用 A::direct_name()

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
