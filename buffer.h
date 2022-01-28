#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "array_ptr.h"

template <typename Type>
class Buffer {
public:
    Buffer() = default;

    explicit Buffer(size_t size) 
    : items_(size + 1),
      begin_(items_.get(), items_.get(), items_.get() + size),
      end_(items_.get() + size, items_.get(), items_.get() + size) {
        size_ = size; 
        capacity_ = size;
    }

    explicit Buffer(std::initializer_list<Type> list)
        : Buffer(list.size()) {
            std::copy(list.begin(), list.end(), begin());
        } 

public:
    template <typename ValueType>
    class Iterator : public std::iterator<std::forward_iterator_tag, ValueType> {
    public:
        friend class Buffer;
    public:
        Iterator() = default;
        Iterator(ValueType* ptr) 
            : ptr_(ptr) {}
        Iterator(ValueType* ptr, ValueType* head, ValueType* tail) 
            : ptr_(ptr),
              head_(head),
              tail_(tail) {}
        Iterator(const Iterator& other) 
            : ptr_(other.ptr_),
              head_(other.head_),
              tail_(other.tail_) {}
    public:
        Iterator operator++() {
            ++ptr_;
            if (ptr_ == tail_ + 1) {
                this->ptr_ = head_;
            }
            return *this;
        }

        Iterator operator--() {
            --ptr_;
            if (ptr_ == head_ - 1) {
                this->ptr_ = tail_;
            }
            return *this;
        }

        Iterator operator++(int) {
            auto old(*this);
            ++(*this);
            return old;
        }

        ValueType& operator*() const {
            return *ptr_;
        }

        bool operator==(const Iterator& other) {
            //
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) {
            //
            return !(ptr_ == other.ptr_);
        }
    private:
        ValueType* ptr_ = nullptr;
        ValueType* head_ = nullptr;
        ValueType* tail_ = nullptr;
    };

public:
    // push_front: complexity - O(1)
    void push_front(const Type& value) {
        if (is_full()) {
            auto position = end_;
            *position = value;
            --end_;
            begin_ = position;
        }
        else {
            --begin_;
            *begin_ = value;
            ++size_;
        }
    }

    // push_back: complexity - O(1)
    void push_back(const Type& value) {
        if (is_full()) {
            auto position = end_;
            end_ = begin_++;
            *position = value;
        }
        else {
            auto position = end_++;
            *position = value;
            ++size_;
        }
    }   

    // pop_front: complexity - O(1)
    void pop_front() {
        if (!is_empty()) {
            ++begin_;
            --size_;
        }
    }

    bool is_empty() const {
        return size_ == 0;
    }

    bool is_full() const {
        return size_ == capacity_;
    }

    size_t size() const {
        return size_;
    }

    size_t max_size() const {
        return capacity_;
    }

    void clear() {
        size_ = 0;
        begin_(items_.get(), items_.get(), items_.get() + size);
        end_(items_.get() + size, items_.get(), items_.get() + size);
    }

    Iterator<Type> begin() noexcept {
        return begin_;
    }

    Iterator<Type> end() noexcept {
        return end_;
    }

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    ArrayPtr<Type> items_;
    Iterator<Type> begin_;
    Iterator<Type> end_;
};