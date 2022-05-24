#pragma once

#include <utility>

template<typename T>
class Line {
    std::pair<T, T> start_pt_, stop_pt_;
    //should be private but currently like that...
    public:
    T a_;
    T b_;
    T c_;

    void normalize();

    public:
    explicit Line(const T x1, const T y1, const T x2, const T y2);
    T calc_dist( std::pair<T, T> &pt);
    T calc_squared_dist( std::pair<T, T> &pt);
};