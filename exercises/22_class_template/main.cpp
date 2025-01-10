﻿#include "../exercise.h"
#include <cstring> // 引入 cstring 以使用 std::memcpy
#include <stdexcept> // 引入 stdexcept 以使用 std::invalid_argument

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 填入正确的 shape 并计算 size
        for(int d = 0; d < 4; ++d){
            shape[d] = shape_[d];
            size *= shape[d];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;
    Tensor4D& operator=(Tensor4D const &) = delete;
    Tensor4D& operator=(Tensor4D &&) noexcept = delete;

    // 这个加法需要支持“单向广播”。
    // 具体来说，`others` 可以具有与 `this` 不同的形状，形状不同的维度长度必须为 1。
    // `others` 长度为 1 但 `this` 长度不为 1 的维度将发生广播计算。
    // 例如，`this` 形状为 `[1, 2, 3, 4]`，`others` 形状为 `[1, 2, 1, 4]`，
    // 则 `this` 与 `others` 相加时，3 个形状为 `[1, 2, 1, 4]` 的子张量各自与 `others` 对应项相加。
    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查 `others` 的形状是否可以广播到 `this`
        for(int d = 0; d < 4; ++d){
            if(!(others.shape[d] == 1 || others.shape[d] == this->shape[d])){
                throw std::invalid_argument("Shapes are not compatible for broadcasting.");
            }
        }

        // 计算 `this` 和 `others` 的总大小
        unsigned int size_this = 1;
        unsigned int size_others = 1;
        for(int d = 0; d < 4; ++d){
            size_this *= this->shape[d];
            size_others *= others.shape[d];
        }

        // 使用嵌套循环遍历所有元素并进行加法操作
        // 假设使用行主序（Row-major order）
        for(unsigned int i = 0; i < this->shape[0]; ++i){
            for(unsigned int j = 0; j < this->shape[1]; ++j){
                for(unsigned int k = 0; k < this->shape[2]; ++k){
                    for(unsigned int l = 0; l < this->shape[3]; ++l){
                        // 计算 `others` 中对应的索引
                        unsigned int o_i = (others.shape[0] == 1) ? 0 : i;
                        unsigned int o_j = (others.shape[1] == 1) ? 0 : j;
                        unsigned int o_k = (others.shape[2] == 1) ? 0 : k;
                        unsigned int o_l = (others.shape[3] == 1) ? 0 : l;

                        // 计算线性索引
                        unsigned int idx_this = i * this->shape[1] * this->shape[2] * this->shape[3] + 
                                                j * this->shape[2] * this->shape[3] + 
                                                k * this->shape[3] + 
                                                l;

                        unsigned int idx_others = o_i * others.shape[1] * others.shape[2] * others.shape[3] + 
                                                   o_j * others.shape[2] * others.shape[3] + 
                                                   o_k * others.shape[3] + 
                                                   o_l;

                        // 进行加法操作
                        this->data[idx_this] += others.data[idx_others];
                    }
                }
            }
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        Tensor4D<int> t0(shape, data);
        Tensor4D<int> t1(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        Tensor4D<float> t0(s0, d0);
        Tensor4D<float> t1(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        Tensor4D<double> t0(s0, d0);
        Tensor4D<double> t1(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
    return 0;
}
