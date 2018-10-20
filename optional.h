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

    optional(T const &a) : is_none(false) {
        new(&data) T(a);
    }

    optional(optional const& other) : is_none(other.is_none)  {
        if (!is_none) {
            new(&data) T(*other);
        }
    }

    ~optional() {
        if (!is_none) {
            (*this)->T::~T();
        }
    }

    optional& operator=(optional const& other) {
        optional tmp = other;
        swap(tmp);
        return *this;
    }

    void swap(optional& other)
    {
        if (!is_none)
        {
            if (!other.is_none)
            {
                std::swap(**this, *other);
            }
            else
            {
                new (&other.data) T(**this);
                get_ptr()->T::~T();
                std::swap(is_none, other.is_none);
            }
        }
        else
        {
            if (!other.is_none)
            {
                new (&data) T(*other);
                other.get_ptr()->T::~T();
                std::swap(is_none, other.is_none);
            }
        }
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
        //assert(!is_none);
        return *get_ptr();
    }

    T const& operator*() const {
        //assert(!is_none);
        return *get_ptr();
    }

    T* operator->() {
        //assert(!is_none);
        return get_ptr();
    }

    T const operator->() const {
        //assert(!is_none);
        return get_ptr();
    }

    template<typename V>
    friend void swap(optional<V>& a, optional<V>& b);
private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
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
        return !(a <= b);
    }
};

template<typename V>
void swap(optional<V> &a, optional<V> &b) {
    a.swap(b);
}

#endif //OPTIONAL_OPTIONAL_H
