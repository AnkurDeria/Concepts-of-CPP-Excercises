#pragma once
#include <iostream>
#include <cmath>

template<typename T> constexpr T __gcd (T a, T b)
{
    return (a==0 && b!=0) ? b: __gcd(b%a, a);
}

template <typename M, typename N>
constexpr auto gcd(const M& m, const N& n)
{
    return __gcd(m, n); 
}

template <typename M, typename ...Rest>
constexpr auto gcd(const M& first, const Rest&... rest)
{ 
    return __gcd(first, gcd(rest...));  
}

template <typename M, typename N>
constexpr auto mcm(const M& m, const N& n)
{
    return m * n /__gcd(m, n); 
}

template <typename M, typename ...Rest>
constexpr auto mcm(const M& first, const Rest&... rest)
{ 
    return mcm(first, mcm(rest...));  
}

template <int base, int exponent, int modules>
struct Power {
    static constexpr int value = (Power<base, exponent-1, modules>::value) * base % modules;
};

template<int base, int modules>
struct Power<base, 0, modules> {
    static constexpr int value = 1 % modules;
};
