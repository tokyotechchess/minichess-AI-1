#pragma once

template <typename T>
T max(T a, T b) { return (a > b) ? a : b; };
template <typename T>
T min(T a, T b) { return (a < b) ? a : b; };
template <typename T>
T abs(T a) { return a > 0 ? a : -a; };