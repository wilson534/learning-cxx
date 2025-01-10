#include "../exercise.h"
#include <memory>
#include <cstring>
#include <string>
#include <vector>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "Initial use_count should be 4.");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "After ptrs[0].reset(), use_count should be 3.");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "After ptrs[1] = nullptr, use_count should be 2.");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "After ptrs[2] = make_shared, use_count should be 1.");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "After assigning shared to ptrs[0], ptrs[1], and moving to ptrs[2], use_count should be 3.");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "After moving ptrs[0] and ptrs[2], use_count should be 2.");

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "After locking observer, use_count should be 3.");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "After resetting all shared_ptrs, use_count should be 0.");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "After locking a destroyed weak_ptr, use_count should still be 0.");

    return 0;
}
