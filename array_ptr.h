#pragma once 

// smart pointer
template <typename Type>
class ArrayPtr{
public:
    ArrayPtr() = default;

    explicit ArrayPtr(size_t size) {
        (size != 0) ? (raw_ptr_ = new Type[size]) : raw_ptr_;
    }

    ~ArrayPtr() {
        delete[] raw_ptr_;
    }
 
    Type* get() const noexcept {
        return raw_ptr_;
    }

private:
    Type* raw_ptr_ = nullptr;
};
