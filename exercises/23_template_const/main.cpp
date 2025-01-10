#include "../exercise.h"
#include <cstring>   // 引入 cstring 以使用 std::memcpy 和 std::memset
#include <stdexcept> // 引入 stdexcept 以使用 std::invalid_argument

// READ: 模板非类型实参 <https://zh.cppreference.com/w/cpp/language/template_parameters#%E6%A8%A1%E6%9D%BF%E9%9D%9E%E7%B1%BB%E5%9E%8B%E5%AE%9E%E5%8F%82>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size
        for(unsigned int d = 0; d < N; ++d){
            shape[d] = shape_[d];
            size *= shape[d];
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }

    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;
    Tensor& operator=(Tensor const &) = delete;
    Tensor& operator=(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }

    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;
        // 采用行主序计算线性索引
        for(int d = N - 1; d >= 0; --d){
            ASSERT(indices[d] < shape[d], "Invalid index");
            index += indices[d] * stride;
            stride *= shape[d];
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2"); // 2*3*4*5 + 2*4*5 + 3*5 + 4 = 120-1=119
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        // 3*8*128 + 4*128 + 99 = 3072 + 512 + 99 = 3683
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
