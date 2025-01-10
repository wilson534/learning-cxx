#include "../exercise.h"
#include <numeric>
#include <cstring>
#include <string>
#include <vector>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    
    // 调用 `std::accumulate` 计算张量占用的字节数
    int size = std::accumulate(shape, shape + 4, 1, [](int a, int b) -> int {
        return a * b;
    }) * sizeof(DataType);
    
    ASSERT(size == 602112, "1x3x224x224 * 4 bytes = 602112");
    return 0;
}
