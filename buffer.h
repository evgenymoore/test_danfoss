#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "array_ptr.h"

template <typename Type>
class Buffer {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

public:
    Buffer() = default;

    explicit Buffer(std::initializer_list<Type> list) 
        : items_(list.size()),
          size_(list.size()), 
          capacity_(list.size()),
          begin_(items_.get()),
          end_(items_.get() + list.size()) {
              std::copy(list.begin(), list.end(), begin());
        }
    
public:
    // push_front: complexity - O(1)
    void push_front(const Type& value) {
        if (size_ < capacity_) {
            *(--begin_) = std::move(value);
            ++size_;
        }
        else {
            
        }
    }

    // push_back: complexity - O(1)
    void push_back(const Type& value) {
        
    }

    // pop_front: complexity - O(1)
    void pop_front() {
        if (size_ > 0) {
            ++begin_;
            --size_;
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t max_size() const {
        return capacity_;
    }

    void clear() {
        size_ = 0;
    }

    Type& operator[](size_t index) {
        if (index >= size_) {
            throw std::invalid_argument("Wrong index!"); 
        }
        return *(begin() + index);
    }

    Iterator begin() noexcept {
        return begin_;
    }

    Iterator end() noexcept {
        return end_;
    }
    
private:
    size_t size_;
    size_t capacity_;
    ArrayPtr<Type> items_;
    Iterator begin_;
    Iterator end_;
};