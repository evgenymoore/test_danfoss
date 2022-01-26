#include <iostream>
#include <cassert>

#include "buffer.h"

int main() {
    Buffer<int> buffer ({1, 2, 3, 4});

    for (auto& value : buffer) {
        std::cout << value;
    }
    std::cout << std::endl;

    // push_front() for size_ = capacity_
    buffer.push_front(5);
    assert(buffer[0] == 5);

    // clear()
    buffer.clear();
    assert(buffer.size() == 0);
    assert(buffer.max_size() == 4);

    // push_back() for size_ < capacity_
    buffer.push_back(5);
    buffer.push_back(4);
    buffer.push_back(3);
    assert(buffer[0] == 5);
    assert(buffer.size() == 3);
    assert(buffer.max_size() == 4);

    // pop_front()
    buffer.pop_front();
    assert(buffer[0] == 4);
    assert(buffer[1] == 3);
    assert(buffer.size() == 2);

    // push_front for size_ < capacity_
    buffer.push_front(1);
    assert(buffer[0] == 1);
    assert(buffer[1] == 4);
    assert(buffer.size() == 3);

    // clear buffer via pop_front()
    while (!buffer.empty()) {
        buffer.pop_front();
    }
    assert(buffer.size() == 0);

    return 0;
}