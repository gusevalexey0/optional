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
    optional() : is_none(true) {}

    optional(T const &a) : is_none(false), data(a) {}

    optional(optional const& other) = default;


    optional& operator=(optional const& other) {
        if (*this != *other) {
            if (!is_none) {
                delete get_ptr();

            }
            is_none = other.is_none;
            if (!is_none) {
                new(get_ptr()) T(*other.get_ptr());
            }
        }
        return *this;
    }

    void clear() {
        if (!is_none) {
            (*this)->T::~T();
        }
        is_none = true;
    }

    explicit operator bool() const {
        return !is_none;
    }

    T& operator*() {
        assert(!is_none);
        return *get_ptr();
    }

    T const& operator*() const {
        assert(!is_none);
        return *get_ptr();
    }

    T* operator->() {
        assert(!is_none);
        return get_ptr();
    }

    T const operator->() const {
        assert(!is_none);
        return get_ptr();
    }

    template<typename V>
    friend void swap(optional<V>& a, optional<V>& b);
private:
    T data;
    bool is_none;

    T* get_ptr() {
        return &reinterpret_cast<T&>(data);
    }

    T const* get_ptr() const {
        return &reinterpret_cast<T const&>(data);
    }

    friend bool operator==(optional const& a, optional const& b) {
        if (a.is_none != b.is_none) {
            return false;
        }

        if (a.is_none) {
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
        return !(a < b);
    }
};

template<typename V>
void swap(optional<V> &a, optional<V> &b) {
    std::swap(a.is_none, b.is_none);
    std::swap(a.data, b.data);
}

#endif //OPTIONAL_OPTIONAL_H
