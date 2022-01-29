#include <iostream>
#include <cassert>
#include <iterator>

#include "buffer.h"

template <typename Type>
void PrintBuffer(Buffer<Type>& buffer) {
    for (auto& value : buffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    Buffer<int> buffer ({1, 2, 3, 4});

    PrintBuffer(buffer);

    buffer.clear();

    PrintBuffer(buffer);

    buffer.push_back(4);
    PrintBuffer(buffer);
    
    buffer.push_front(3);
    PrintBuffer(buffer);

    buffer.push_front(2);
    PrintBuffer(buffer);
    
    buffer.push_front(1);
    PrintBuffer(buffer);

    buffer.push_front(5);
    PrintBuffer(buffer);

    buffer.push_front(6);
    PrintBuffer(buffer);

    buffer.clear();
    buffer.clear();
    buffer.clear();

    PrintBuffer(buffer);

    for (int i = 0; i < 10; ++i) {
        buffer.push_front(i);
        PrintBuffer(buffer);
    }

    // assert(buffer.size() == 0);
    // assert(buffer.begin() == buffer.end());

    // // push_front() for size_ = capacity_
    // buffer.push_front(5);
    // assert(buffer[0] == 5);

    // // clear()
    // buffer.clear();
    // assert(buffer.size() == 0);
    // assert(buffer.max_size() == 4);

    // // push_back() for size_ < capacity_
    // buffer.push_back(5);
    // buffer.push_back(4);
    // buffer.push_back(3);
    // assert(buffer[0] == 5);
    // assert(buffer.size() == 3);
    // assert(buffer.max_size() == 4);

    // pop_front()
    // buffer.pop_front();
    // assert(buffer[0] == 4);
    // assert(buffer[1] == 3);
    // assert(buffer.size() == 2);

    // // push_front for size_ < capacity_
    // buffer.push_front(1);
    // assert(buffer[0] == 1);
    // assert(buffer[1] == 4);
    // assert(buffer.size() == 3);

    // // clear buffer via pop_front()
    // while (!buffer.empty()) {
    //     buffer.pop_front();
    // }
    // assert(buffer.size() == 0);
    // assert(buffer.begin() == buffer.end());

    return 0;
}