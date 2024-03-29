#include <iostream>
#include <cassert>
#include <iterator>

#include "buffer.h"

template <typename Type>
void PrintBuffer(Buffer<Type>& buffer) {
    if (buffer.is_empty()) {
        std::cout << "empty buffer";
    }
    else {
        for (auto& value : buffer) {
            std::cout << value;
        }
    }
    std::cout << std::endl;
}

int main() {
    // tests
    {
        Buffer<int> buffer ({1, 2, 3, 4});
        PrintBuffer(buffer);

        buffer.push_front(0);
        PrintBuffer(buffer);

        buffer.push_back(5); 
        PrintBuffer(buffer); 

        buffer.pop_front(); 

        for (auto& value : buffer) {
            std::cout << value;
        }
        std::cout << std::endl;

        std::cout << buffer.size() << std::endl;
        std::cout << buffer.max_size() << std::endl;

        buffer.clear(); 
        PrintBuffer(buffer);
        std::cout << std::endl;
    }

    // extra tests
    {
        Buffer<int> buffer ({1, 2, 3, 4});
        PrintBuffer(buffer);

        // clear()
        buffer.clear();
        assert(buffer.size() == 0);
        assert(buffer.begin() == buffer.end());
        assert(buffer.max_size() == 4);
        PrintBuffer(buffer);

        // push_front()
        buffer.push_front(5);
        assert(*buffer.begin() == 5);
        PrintBuffer(buffer);

        // push_back() for size_ < capacity_
        buffer.push_back(5);
        buffer.push_back(4);
        buffer.push_back(3);
        assert(*buffer.begin() == 5);
        assert(buffer.size() == 4);
        assert(buffer.max_size() == 4);
        PrintBuffer(buffer);

        // pop_front()
        buffer.pop_front();
        assert(*buffer.begin() == 5);
        assert(buffer.size() == 3);
        PrintBuffer(buffer);

        // push_front for size_ < capacity_
        buffer.push_front(1);
        assert(*buffer.begin() == 1);
        assert(buffer.size() == 4);
        PrintBuffer(buffer);

        // clear buffer via pop_front()
        while (!buffer.is_empty()) {
            buffer.pop_front();
        }
        assert(buffer.size() == 0);
        assert(buffer.begin() == buffer.end());
        PrintBuffer(buffer);
    }

    return 0;
}