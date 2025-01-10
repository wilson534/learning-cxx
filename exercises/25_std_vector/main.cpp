﻿#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        ASSERT(sizeof(vec) == sizeof(void*) * 3, "Fill in the correct value."); // 通常 std::vector 包含指向数据的指针、大小和容量，假设每个为指针大小
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(void*) * 3, "Fill in the correct value."); // 同上，通常为 24 字节（3 * 8 字节）在 64 位系统上
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(void*) * 3, "Fill in the correct value."); // sizeof(vec) 不变，因为它只是管理指针
            vec.pop_back();
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == sizeof(void*) * 3, "Fill in the correct value.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1.0, "Fill in the correct value.");
            ASSERT(vec[1] == 2.0, "Fill in the correct value.");
            ASSERT(vec[2] == 3.0, "Fill in the correct value.");
            ASSERT(vec[3] == 4.0, "Fill in the correct value.");
            ASSERT(vec[4] == 6.0, "Fill in the correct value.");
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            // 插入：平均情况为 O(n)，删除：O(n)
            vec.insert(vec.begin() + 1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            vec.erase(vec.begin() + 3);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            ASSERT(vec.capacity() >= vec.size(), "Fill in the correct value."); // shrink_to_fit 可能不会减少 capacity，但至少不增加
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            ASSERT(vec.capacity() >= 0, "Fill in the correct value."); // capacity() 不会减少到0，取决于实现
        }
    }
    {
        std::vector<char> vec(48, 'z'); // TODO: 调用正确的构造函数
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == sizeof(void*) * 3, "Fill in the correct value."); // 通常为 24 字节在 64 位系统上
        {
            auto capacity = vec.capacity();
            vec.resize(16);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == capacity, "Fill in a correct identifier."); // resize 不改变 capacity
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() >= 256, "Fill in the correct value.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value.");
            ASSERT(vec.capacity() >= 256, "Fill in the correct value.");
            ASSERT(vec[15] == 'z', "Fill in the correct value.");
            ASSERT(vec[16] == 'a', "Fill in the correct value.");
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}