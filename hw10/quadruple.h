#pragma once

#include <array>

template <typename T, typename U, typename V, typename W> 
struct Quadruple {
public:
    Quadruple(T _first, U _second, V _third, W _fourth) {
        first = _first;
        second = _second;
        third = _third;
        fourth = _fourth;
    }

    T get_first() {
        return first;
    }
    U get_second() {
        return second;
    }
    V get_third() {
        return third;
    }
    W get_fourth() {
        return fourth;
    }
private:
    T first;
    U second;
    V third;
    W fourth;
};

template<>
struct Quadruple<int, int, int, int> {
public:
    Quadruple(int _first, int _second, int _third, int _fourth) {
        members[0] = _first;
        members[1] = _second;
        members[2] = _third;
        members[3] = _fourth;
    }

    int get_first() {
        return members[0];
    }
    int get_second() {
        return members[1];
    }
    int get_third() {
        return members[2];
    }
    int get_fourth() {
        return members[3];
    }
public:
    std::array<int, 4> members;
};


template<typename T>
struct Quadruple<T, T, T, T> {
public:
    Quadruple(T _first, T _second, T _third, T _fourth) {
        members[0] = _first;
        members[1] = _second;
        members[2] = _third;
        members[3] = _fourth;
    }

    T get_first() {
        return members[0];
    }
    T get_second() {
        return members[1];
    }
    T get_third() {
        return members[2];
    }
    T get_fourth() {
        return members[3];
    }
public:
    std::array<T, 4> members;
};

