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
          capacity_(list.size()) {
              std::copy(list.begin(), list.end(), begin());
        }
    
public:
    void push_front(Type&& value) {
        if (size_ == capacity_) {
            for (size_t i = size_ - 1; i > 0; --i) {
                std::swap(items_[i], items_[i - 1]);
            }
            items_[0] = std::move(value);
        }
        else {
            ++size_;
            std::move(begin(), begin() + size(), begin() + 1);
            *begin() = std::move(value);
        }
    }

    void push_back(Type&& value) {
        if (size_ == capacity_) {
            for (int i = 0; i < size_ - 1; ++i) {
                std::swap(items_[i], items_[i + 1]);
            }
            items_[size_ - 1] = std::move(value);
        }
        else {
            items_[size_++] = std::move(value);
        }
    }

    void pop_front() {
        std::move(begin() + 1, begin() + size(), begin());
        --size_;
    }

    bool empty() const {
        return size() == 0;
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
        return *(items_.get() + index);
    }

    Iterator begin() noexcept {
        return items_.get();
    }

    Iterator end() noexcept {
        return items_.get() + size_;
    }

private:
    size_t size_;
    size_t capacity_;

    ArrayPtr<Type> items_;
};