#include "../exercise.h"
#include <cmath>    // 用于 std::exp 和 std::abs
#include <iostream> // 用于输出（如果需要调试）

enum class DataType {
    Float,
    Double,
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union {
        float f;
        double d;
    };

    // 构造函数，确保联合体正确初始化
    TaggedUnion(DataType t) : type(t), f(0.0f) {} // 默认初始化为 float
};

// TODO: 将这个函数模板化
template <typename T>
T sigmoid(T x) {
    return 1 / (1 + std::exp(-x));
}

/// @brief 辅助函数，用于比较两个浮点数是否近似相等
template <typename T>
bool almost_equal(T a, T b, T epsilon = static_cast<T>(1e-6)) {
    return std::abs(a - b) < epsilon;
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    // TODO: 根据 type 调用 sigmoid
    if (x.type == DataType::Float) {
        ans.f = sigmoid(x.f);
    } else if (x.type == DataType::Double) {
        ans.d = sigmoid(x.d);
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    // 测试 float 类型
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    // 使用 almost_equal 进行浮点数比较
    ASSERT(almost_equal(yf.f, 1 / (1 + std::exp(-5.f))), "sigmoid float");

    // 测试 double 类型
    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(almost_equal(yd.d, 1 / (1 + std::exp(-5.0))), "sigmoid double");

    return 0;
}
