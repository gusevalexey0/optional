//
// Created by qw on 20.10.18.
//

#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <algorithm>
#include <cassert>
template <typename T>
struct optional {
public:
    optional() : is_empty(true) {}

    optional(T const &a) : is_empty(false) {
        new(&data) T(a);
    }

    optional(optional const& other) : is_empty(other.is_empty)  {
        if (!is_empty) {
            new(&data) T(*other);
        }
    }

    ~optional() {
        clear();
    }

    optional& operator=(optional const& other) {
        if (this == &other) { return *this; }
        clear();
        if (!other.is_empty) {
            new(&data) T(*other);
        }
        is_empty = other.is_empty;
        return *this;
    }

    void swap(optional& other)
    {
        optional temp = other;
        other = *this;
        *this = temp;
    }

    void clear() {
        if (!is_empty) {
            (*this)->T::~T();
        }
        is_empty = true;
    }

    explicit operator bool() const {
        return !is_empty;
    }

    T& operator*() {
        //assert(!is_empty);
        return *get_ptr();
    }

    T const& operator*() const {
        //assert(!is_empty);
        return *get_ptr();
    }

    T* operator->() {
        //assert(!is_empty);
        return get_ptr();
    }

    T const operator->() const {
        //assert(!is_empty);
        return get_ptr();
    }

    template<typename V>
    friend void swap(optional<V>& a, optional<V>& b);
private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
    bool is_empty;

    T* get_ptr() {
        return reinterpret_cast<T*>(&data);
    }

    T const* get_ptr() const {
        return reinterpret_cast<T const*>(&data);
    }

    friend bool operator==(optional const& a, optional const& b) {
        if (a.is_empty != b.is_empty) {
            return false;
        }

        if (a.is_empty && b.is_empty) {
            return true;
        }

        return *a == *b;
    }

    friend bool operator!=(optional const& a, optional const& b) {
        return !(a == b);
    }

    friend bool operator<(optional const& a, optional const& b) {
        if (a) {
            return b ? *a < *b : false;
        } else {
            return b ? true : false;
        }

    }

    friend bool operator<=(optional const& a, optional const& b)
    {
        return a < b || a == b;
    }

    friend bool operator>=(optional const& a, optional const& b)
    {
        return a > b || a == b;
    }

    friend bool operator>(optional const& a, optional const& b) {
        return !(a <= b);
    }
};

template<typename V>
void swap(optional<V> &a, optional<V> &b) {
    a.swap(b);
}

#endif //OPTIONAL_OPTIONAL_H
